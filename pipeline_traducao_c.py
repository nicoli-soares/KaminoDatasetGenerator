# -*- coding: utf-8 -*-
"""
Pipeline automatizado de traducao BigCodeBench (Python) -> C

Segue a mesma filosofia das 3 etapas centrais do Kamino original:
  1. Generation  -> pede ao LLM (via Ollama) para traduzir Python para C
  2. Testing     -> compila e roda os testes traduzidos automaticamente
  3. Repairing   -> se falhar, reenvia o erro ao LLM para tentar corrigir

Requisitos:
  - Ollama rodando localmente, com o modelo configurado em
    pipeline/resources/ollama_config_local.json ja baixado (ollama pull)
  - Biblioteca 'ollama' instalada (ja vem no requirements.txt do projeto)
  - gcc disponivel no PATH

Como usar:
  python pipeline_traducao_c.py                    (usa o modelo do config)
  python pipeline_traducao_c.py deepseek-r1:14b     (forca um modelo especifico)
  python pipeline_traducao_c.py qwen2.5:3b          (ideal para comparar modelos)

Saida (nomeada por modelo, para nao sobrescrever ao comparar varios):
  - traducoes_automaticas_<modelo>/<ID>/funcao.py   (codigo Python original)
  - traducoes_automaticas_<modelo>/<ID>/programa.c  (traducao + testes gerados)
  - relatorio_pipeline_<modelo>.json                (resumo de sucesso/falha)
"""

import json
import os
import re
import sys
import subprocess
import shutil

import ollama

# ============================================================
# CONFIGURACAO
# ============================================================

CAMINHO_DATASET = "dataset/bigcodebench_normalized_filtered.json"
CAMINHO_CONFIG_OLLAMA = "pipeline/resources/ollama_config_local.json"
CAMINHO_GUIA = "guia_traducao_python_c.md"

MAX_TENTATIVAS = 5          # tentativas de reparo por entrada, antes de descartar
TAMANHO_LOTE = 5            # quantas entradas processar nesta execucao

# Definidos em main(), com base no modelo escolhido (permite comparar
# resultados de varios modelos sem que um sobrescreva o outro)
PASTA_SAIDA = None
RELATORIO_SAIDA = None
TIMEOUT_COMPILACAO = 10     # segundos
TIMEOUT_EXECUCAO = 10       # segundos

# Mesmas listas de exclusao do guia / filtrar_piloto.py
LIBS_PROBLEMATICAS = {
    "random", "numpy", "pandas", "os", "unittest.mock", "statistics",
    "sklearn", "matplotlib", "scipy",
    "requests", "flask", "flask_restful", "django", "urllib", "socket",
    "bs4", "http", "smtplib", "ftplib",
    "psutil", "platform", "subprocess", "shutil", "multiprocessing",
    "threading",
    "zlib", "gzip", "cryptography", "hashlib", "zipfile", "struct",
    "pickle",
    "sqlite3", "sqlalchemy",
    "ipaddress",
    "nltk", "faker", "geopy", "folium", "docx",
    "glob", "xmltodict", "prettytable", "unicodedata", "pytz",
    "inspect", "types", "yaml", "dateutil",
}

PADROES_NAO_DETERMINISTICOS = [
    ".now(", "datetime.today(", "time.time(", "time.localtime(",
]

MAX_LINHAS_CODIGO = 20  # um pouco mais permissivo que no piloto

# IDs ja traduzidos manualmente (10 da Semana 3-4 + 5 do piloto) - nao repetir
JA_TRADUZIDAS = {
    "BigCodeBench/4", "BigCodeBench/297", "BigCodeBench/254",
    "BigCodeBench/270", "BigCodeBench/97", "BigCodeBench/172",
    "BigCodeBench/178", "BigCodeBench/358", "BigCodeBench/7",
    "BigCodeBench/96", "BigCodeBench/667", "BigCodeBench/327",
    "BigCodeBench/669", "BigCodeBench/666", "BigCodeBench/682",
}


# ============================================================
# ETAPA 0: SELECAO DE CANDIDATAS (mesma logica do filtrar_piloto.py)
# ============================================================

def eh_candidata_boa(entrada):
    if entrada.get("id") in JA_TRADUZIDAS:
        return False

    codigo = entrada.get("original_code", "")
    metadata = entrada.get("metadata", {})
    libs_str = metadata.get("libs", "[]")

    try:
        libs = eval(libs_str) if isinstance(libs_str, str) else libs_str
    except Exception:
        libs = []

    if any(lib in LIBS_PROBLEMATICAS for lib in libs):
        return False

    if metadata.get("split") and metadata["split"] != "easy":
        return False

    num_linhas = len([l for l in codigo.split("\n") if l.strip()])
    if num_linhas > MAX_LINHAS_CODIGO:
        return False

    if "random." in codigo or "np." in codigo or "numpy." in codigo:
        return False

    if any(padrao in codigo for padrao in PADROES_NAO_DETERMINISTICOS):
        return False

    if "class " in codigo:
        return False

    # Exclui casos com listas aninhadas / matrizes (list of lists), que se
    # mostraram uma fonte recorrente de erro tanto para traducao manual
    # quanto automatizada (confusao de niveis de ponteiro em C)
    params_str = entrada.get("metadata", {}).get("params", "")
    padroes_lista_aninhada = ["list of lists", "list_of_lists", "List[List[", "matrix", "matriz"]
    if any(p.lower() in codigo.lower() or p.lower() in params_str.lower() for p in padroes_lista_aninhada):
        return False

    return True


def carregar_candidatas():
    with open(CAMINHO_DATASET, "r", encoding="utf-8") as f:
        dados = json.load(f)
    candidatas = [e for e in dados if eh_candidata_boa(e)]
    return candidatas[:TAMANHO_LOTE]


# ============================================================
# CONFIGURACAO DO LLM
# ============================================================

def carregar_modelo():
    # Se um modelo foi passado como argumento de linha de comando, usa ele
    # (permite comparar modelos sem precisar editar o arquivo de config)
    if len(sys.argv) > 1:
        return sys.argv[1]

    with open(CAMINHO_CONFIG_OLLAMA, "r", encoding="utf-8") as f:
        config = json.load(f)
    # O campo "model" fica aninhado dentro de "json", nao na raiz do arquivo
    return config.get("json", {}).get("model", "qwen2.5-coder:7b")


def nome_seguro_modelo(modelo):
    """Converte o nome do modelo em algo seguro para usar em nomes de arquivo/pasta."""
    return re.sub(r'[^\w\-.]', '_', modelo)


def carregar_guia():
    if os.path.exists(CAMINHO_GUIA):
        with open(CAMINHO_GUIA, "r", encoding="utf-8") as f:
            return f.read()
    return "(guia nao encontrado - traduza seguindo boas praticas de C)"


# ============================================================
# ETAPA 1: GENERATION (montar prompt e chamar o LLM)
# ============================================================

def montar_prompt_inicial(entrada, guia_texto):
    codigo = entrada["original_code"]
    testes = "\n\n".join(entrada.get("test", []))

    prompt = f"""Voce e um tradutor de codigo Python para C, seguindo ESTRITAMENTE
as regras abaixo (extraidas de um guia validado em 15 traducoes anteriores):

{guia_texto}

TAREFA: Traduza a funcao Python abaixo para C, e traduza tambem os testes
reais fornecidos (NAO invente novos testes). Se algum teste depender de
random, numpy, Faker, ou checar apenas tipo (isinstance), OMITA esse teste
especifico e explique o motivo em um comentario no codigo.

REGRAS CRITICAS (sao a causa mais comum de falha - siga com atencao):
1. Escreva TUDO em um UNICO bloco de codigo: a funcao traduzida, as funcoes
   de teste, e a funcao main() que executa os testes - tudo junto, na ordem
   que fizer sentido (structs/funcao primeiro, depois os testes, depois main).
2. NAO use #include de arquivos personalizados (como "task_func.h" ou
   qualquer .h que voce mesmo inventar) - o codigo deve ser totalmente
   autocontido em um unico arquivo.
3. NAO inclua #include de bibliotecas padrao (stdio.h, stdlib.h, string.h,
   math.h, ctype.h) - isso ja e adicionado automaticamente. Comece direto
   pelas structs/funcoes.
4. NUNCA chame uma funcao que voce mesmo nao implementou. C nao tem
   bibliotecas equivalentes as bibliotecas Python (base64, html, textwrap,
   json, yaml). Se precisar dessa logica, implemente voce mesmo em C puro.
5. Todo tipo customizado (struct, typedef) usado deve ser definido antes de
   ser usado, com um nome especifico para este problema (nunca use nomes
   genericos de exemplo de forma literal).

Responda EXATAMENTE neste formato, sem texto adicional fora do bloco:

```c_programa
<codigo C completo: structs/typedefs necessarios, a funcao traduzida,
as funcoes de teste, e a funcao main() que executa tudo - em um unico bloco>
```

Codigo Python original:
```python
{codigo}
```

Testes Python originais:
```python
{testes}
```
"""
    return prompt


def montar_prompt_reparo(entrada, codigo_anterior, mensagem_erro):
    return f"""A traducao anterior falhou. Aqui esta o erro exato:

ERRO:
{mensagem_erro}

Codigo C da tentativa anterior:
```c
{codigo_anterior}
```

Corrija o problema e responda de novo EXATAMENTE no formato:

```c_programa
<codigo C completo corrigido>
```
"""


def chamar_llm(modelo, mensagens):
    try:
        resposta = ollama.chat(
            model=modelo,
            messages=mensagens,
            options={"num_ctx": 16384}  # aumenta a janela de contexto (padrao do Ollama e so 4096)
        )
        return resposta["message"]["content"], None
    except Exception as e:
        # Nunca deixa um erro de comunicacao com o LLM derrubar o script inteiro -
        # trata como uma tentativa falha, igual a um erro de compilacao/teste
        return None, f"ERRO NA CHAMADA AO LLM: {e}"


def extrair_blocos(texto_resposta):
    """Extrai o bloco unico c_programa da resposta do LLM."""
    match = re.search(r"```c_programa\s*(.*?)```", texto_resposta, re.DOTALL)
    return match.group(1).strip() if match else None


# ============================================================
# ETAPA 2: TESTING (compilar e rodar)
# ============================================================

def compilar_e_testar(codigo_programa, pasta_trabalho):
    os.makedirs(pasta_trabalho, exist_ok=True)
    caminho_c = os.path.join(pasta_trabalho, "programa.c")
    caminho_bin = os.path.join(pasta_trabalho, "programa")

    # Includes padrao adicionados automaticamente - nao dependemos do LLM
    # lembrar disso (Causa raiz identificada no piloto: includes ausentes)
    includes_padrao = (
        "#include <stdio.h>\n"
        "#include <stdlib.h>\n"
        "#include <string.h>\n"
        "#include <math.h>\n"
        "#include <ctype.h>\n"
        "#include <limits.h>\n"
        "#include <assert.h>\n\n"
    )

    # Remove qualquer #include que o LLM tenha gerado por conta propria
    # (tanto includes padrao duplicados quanto headers customizados
    # inventados, como "task_func.h", que nunca existem de verdade)
    def remover_includes(codigo):
        linhas = codigo.split("\n")
        return "\n".join(l for l in linhas if not l.strip().startswith("#include"))

    codigo_limpo = remover_includes(codigo_programa)

    # Verifica se ha mais de um main() dentro do proprio bloco unico
    # (pode acontecer se o LLM, mesmo com um so bloco, ainda repetir algo)
    if codigo_limpo.count("int main(") + codigo_limpo.count("void main(") > 1:
        return False, (
            "ERRO: o codigo contem mais de uma funcao main(). Deve haver "
            "EXATAMENTE UMA funcao main() em todo o programa."
        )

    with open(caminho_c, "w", encoding="utf-8") as f:
        f.write(includes_padrao + codigo_limpo + "\n")

    # Sempre linka -lm (Regra: seguro mesmo se nao usar math.h)
    resultado_compilacao = subprocess.run(
        ["gcc", "-o", caminho_bin, caminho_c, "-lm"],
        capture_output=True, text=True, timeout=TIMEOUT_COMPILACAO
    )

    if resultado_compilacao.returncode != 0:
        return False, f"ERRO DE COMPILACAO:\n{resultado_compilacao.stderr}"

    try:
        resultado_execucao = subprocess.run(
            [caminho_bin], capture_output=True, text=True,
            timeout=TIMEOUT_EXECUCAO
        )
    except subprocess.TimeoutExpired:
        return False, "ERRO: programa entrou em loop infinito ou demorou demais (timeout)"

    if resultado_execucao.returncode != 0:
        return False, (
            f"ERRO DE EXECUCAO (codigo de saida {resultado_execucao.returncode}):\n"
            f"{resultado_execucao.stdout}\n{resultado_execucao.stderr}"
        )

    return True, resultado_execucao.stdout


# ============================================================
# ETAPA 3: REPAIRING + LOOP PRINCIPAL
# ============================================================

def processar_entrada(entrada, modelo, guia_texto):
    entry_id = entrada["id"]
    id_seguro = entry_id.replace("/", "_")
    pasta_trabalho = os.path.join(PASTA_SAIDA, id_seguro)

    mensagens = [
        {"role": "user", "content": montar_prompt_inicial(entrada, guia_texto)}
    ]

    codigo_programa = None
    saida_ou_erro = "Nenhuma tentativa produziu resultado (erro inesperado)"

    for tentativa in range(1, MAX_TENTATIVAS + 1):
        print(f"  [{entry_id}] Tentativa {tentativa}/{MAX_TENTATIVAS}...")

        resposta, erro_llm = chamar_llm(modelo, mensagens)

        if erro_llm is not None:
            # Falha na propria chamada ao LLM (ex: contexto excedido) -
            # nao ha resposta para adicionar ao historico, entao encurtamos
            # a conversa para a proxima tentativa (mantem so o prompt inicial)
            saida_ou_erro = erro_llm
            print(f"    (erro na chamada ao LLM: {erro_llm[:100]}...)")
            mensagens = [{"role": "user", "content": montar_prompt_inicial(entrada, guia_texto)}]
            continue

        codigo_programa = extrair_blocos(resposta)

        if codigo_programa is None:
            saida_ou_erro = "Resposta do LLM nao seguiu o formato esperado (bloco c_programa ausente)"
            mensagens.append({"role": "assistant", "content": resposta})
            mensagens.append({"role": "user", "content": f"Formato invalido. {saida_ou_erro}. Responda novamente no formato correto."})
            continue

        sucesso, saida_ou_erro = compilar_e_testar(codigo_programa, pasta_trabalho)

        if sucesso:
            return {
                "id": entry_id, "status": "sucesso", "tentativas": tentativa,
                "saida": saida_ou_erro
            }, codigo_programa

        # Falhou -> prepara reparo
        mensagens.append({"role": "assistant", "content": resposta})
        mensagens.append({
            "role": "user",
            "content": montar_prompt_reparo(entrada, codigo_programa, saida_ou_erro)
        })

    # Esgotou as tentativas -> descarta
    shutil.rmtree(pasta_trabalho, ignore_errors=True)
    return {
        "id": entry_id, "status": "falha", "tentativas": MAX_TENTATIVAS,
        "ultimo_erro": saida_ou_erro
    }, None


def salvar_traducao_valida(entrada, codigo_programa):
    entry_id = entrada["id"]
    id_seguro = entry_id.replace("/", "_")
    pasta = os.path.join(PASTA_SAIDA, id_seguro)
    os.makedirs(pasta, exist_ok=True)

    with open(os.path.join(pasta, "funcao.py"), "w", encoding="utf-8") as f:
        f.write(entrada["original_code"])

    # Nota: diferente das traducoes manuais (que separam funcao.c e teste.c),
    # a geracao automatizada salva tudo em um unico arquivo programa.c.
    # Essa e uma simplificacao deliberada: pedir ao LLM um unico bloco de
    # codigo (em vez de dois blocos separados) eliminou um problema
    # recorrente de duplicacao de codigo entre os blocos.
    with open(os.path.join(pasta, "programa.c"), "w", encoding="utf-8") as f:
        f.write(codigo_programa)


def main():
    global PASTA_SAIDA, RELATORIO_SAIDA

    print("Carregando modelo, guia e candidatas...")
    modelo = carregar_modelo()
    guia_texto = carregar_guia()
    candidatas = carregar_candidatas()

    # Nomeia a saida com base no modelo, para poder comparar varios
    # modelos sem que a execucao de um sobrescreva o resultado do outro
    sufixo = nome_seguro_modelo(modelo)
    PASTA_SAIDA = f"traducoes_automaticas_{sufixo}"
    RELATORIO_SAIDA = f"relatorio_pipeline_{sufixo}.json"

    print(f"Modelo: {modelo}")
    print(f"Candidatas selecionadas para este lote: {len(candidatas)}\n")

    os.makedirs(PASTA_SAIDA, exist_ok=True)
    relatorio = []

    for i, entrada in enumerate(candidatas, start=1):
        print(f"[{i}/{len(candidatas)}] Processando {entrada['id']}...")
        resultado, codigo_programa = processar_entrada(entrada, modelo, guia_texto)
        relatorio.append(resultado)

        if resultado["status"] == "sucesso":
            salvar_traducao_valida(entrada, codigo_programa)
            print(f"  -> SUCESSO (tentativa {resultado['tentativas']})\n")
        else:
            print(f"  -> DESCARTADA apos {resultado['tentativas']} tentativas\n")

    sucessos = [r for r in relatorio if r["status"] == "sucesso"]
    falhas = [r for r in relatorio if r["status"] == "falha"]

    print("=" * 60)
    print(f"MODELO: {modelo}")
    print(f"RESUMO: {len(sucessos)} sucesso(s), {len(falhas)} falha(s)")
    print(f"Taxa de sucesso: {len(sucessos) / len(candidatas) * 100:.1f}%")
    print("=" * 60)

    with open(RELATORIO_SAIDA, "w", encoding="utf-8") as f:
        json.dump(relatorio, f, indent=2, ensure_ascii=False)

    print(f"\nRelatorio detalhado salvo em: {RELATORIO_SAIDA}")
    print(f"Traducoes validas salvas em: {PASTA_SAIDA}/")


if __name__ == "__main__":
    main()
