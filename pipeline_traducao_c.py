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

Opcoes (todas opcionais; sem elas o comportamento e o mesmo de antes):
  --ponteiros          anexa ao guia a secao guia_ponteiros.md (padroes seguros
                       de ponteiros/memoria em C)
  --incluir-aninhadas  desliga o filtro de listas aninhadas/matrizes (necessario
                       para testar se a secao de ponteiros ajuda justamente
                       nesses casos)
  --lote N             quantas entradas processar (padrao: 5)
  --dataset humaneval  traduz o HumanEval (problemas mais simples) em vez do
                       BigCodeBench. Precisa do arquivo dataset/humaneval.jsonl
                       (gerado por baixar_humaneval.py)
  --arquivo CAMINHO    usa outro arquivo de dataset no lugar do padrao
  --guardar-falhas     nas entradas descartadas, guarda o ultimo codigo gerado
                       (programa.c) e o erro (erro.txt) em <ID>_FALHA/ para analise

Criterio de sucesso: o programa compila, termina com codigo 0 E os testes sao
validos (usam assert() e nao imprimem mensagem de falha). Isso evita "sucessos"
falsos em que o modelo escreve testes que so imprimem o resultado.

Exemplo com o HumanEval:
  python baixar_humaneval.py
  python pipeline_traducao_c.py deepseek-r1:14b --dataset humaneval --ponteiros

Exemplo de comparacao A/B (mesmo modelo, mesmas entradas):
  python pipeline_traducao_c.py deepseek-r1:14b --incluir-aninhadas
  python pipeline_traducao_c.py deepseek-r1:14b --incluir-aninhadas --ponteiros

Saida (nomeada por modelo e opcoes, para nao sobrescrever ao comparar):
  - traducoes_automaticas_<modelo>[_aninhadas][_ponteiros]/<ID>/funcao.py
  - traducoes_automaticas_<modelo>[_aninhadas][_ponteiros]/<ID>/programa.c
  - relatorio_pipeline_<modelo>[_aninhadas][_ponteiros].json
"""

import argparse
import ast
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
CAMINHO_GUIA_PONTEIROS = "guia_ponteiros.md"
CAMINHO_DATASET_HUMANEVAL = "dataset/humaneval.jsonl"
DATASET = "bigcodebench"    # --dataset humaneval troca para o HumanEval
ARQUIVO_DATASET = None      # --arquivo troca o caminho do dataset
GUARDAR_FALHAS = False      # --guardar-falhas guarda o codigo/erro das entradas descartadas

MAX_TENTATIVAS = 5          # tentativas de reparo por entrada, antes de descartar
TAMANHO_LOTE = 5            # quantas entradas processar nesta execucao (--lote N altera)

# Definidos em main(), com base no modelo e nas opcoes escolhidas (permite
# comparar varias execucoes sem que uma sobrescreva o resultado da outra)
PASTA_SAIDA = None
RELATORIO_SAIDA = None
INCLUIR_ANINHADAS = False   # --incluir-aninhadas desliga o filtro de listas aninhadas
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
    # (--incluir-aninhadas desliga este filtro, para testar o guia de ponteiros)
    if not INCLUIR_ANINHADAS:
        params_str = entrada.get("metadata", {}).get("params", "")
        padroes_lista_aninhada = ["list of lists", "list_of_lists", "List[List[", "matrix", "matriz"]
        if any(p.lower() in codigo.lower() or p.lower() in params_str.lower() for p in padroes_lista_aninhada):
            return False

    return True


# ------------------------------------------------------------
# HumanEval (--dataset humaneval)
# Colunas do dataset openai/openai_humaneval: task_id, prompt,
# canonical_solution, test, entry_point. Cada linha e convertida para o
# MESMO formato interno do BigCodeBench (id, original_code, test), entao a
# geracao, o teste e o reparo continuam exatamente iguais.
# ------------------------------------------------------------

def converter_humaneval(linha):
    ponto = linha["entry_point"]
    # prompt = assinatura + docstring; canonical_solution = corpo da funcao
    codigo = linha["prompt"].rstrip() + "\n" + linha["canonical_solution"].rstrip() + "\n"
    # remove o dicionario METADATA (nao e teste) e chama check() com a funcao
    teste = re.sub(r"METADATA\s*=\s*\{.*?\}\s*", "", linha["test"],
                   count=1, flags=re.DOTALL).strip()
    teste += f"\n\ncheck({ponto})"
    return {
        "id": linha["task_id"],
        "original_code": codigo,
        "test": [teste],
        "metadata": {"fonte": "humaneval", "entry_point": ponto},
    }


def ler_humaneval(caminho):
    with open(caminho, "r", encoding="utf-8") as f:
        if caminho.endswith(".jsonl"):
            linhas = [json.loads(l) for l in f if l.strip()]
        else:
            linhas = json.load(f)
    return [converter_humaneval(l) for l in linhas]


def _sem_docstrings(codigo):
    return re.sub(r'""".*?"""|\'\'\'.*?\'\'\'', "", codigo, flags=re.DOTALL)


def _modulos_importados(codigo):
    modulos = set()
    padrao = r"^\s*(?:from\s+([\w.]+)\s+import|import\s+([\w., ]+))"
    for m in re.finditer(padrao, codigo, flags=re.MULTILINE):
        if m.group(1):
            modulos.add(m.group(1))
        else:
            for nome in m.group(2).split(","):
                modulos.add(nome.strip().split(" as ")[0].strip())
    return modulos


def eh_candidata_humaneval(entrada):
    codigo = entrada["original_code"]
    testes = "\n".join(entrada.get("test", []))

    try:
        ast.parse(codigo)
    except SyntaxError:
        return False

    codigo_sem_doc = _sem_docstrings(codigo)

    # Bibliotecas excluidas, no codigo E nos testes (ex.: o teste do
    # HumanEval/32 importa random, o que tornaria o teste nao deterministico)
    for mod in _modulos_importados(codigo) | _modulos_importados(testes):
        if mod in LIBS_PROBLEMATICAS or mod.split(".")[0] in LIBS_PROBLEMATICAS:
            return False

    # Tamanho: conta so as linhas de codigo (a docstring do HumanEval e longa)
    num_linhas = len([l for l in codigo_sem_doc.split("\n") if l.strip()])
    if num_linhas > MAX_LINHAS_CODIGO:
        return False

    for texto in (codigo_sem_doc, testes):
        if "random." in texto or "np." in texto or "numpy." in texto:
            return False
        if any(padrao in texto for padrao in PADROES_NAO_DETERMINISTICOS):
            return False

    if "class " in codigo_sem_doc:
        return False

    if not INCLUIR_ANINHADAS:
        baixo = codigo.lower()
        padroes_lista_aninhada = ["list of lists", "list_of_lists", "list[list[", "matrix", "matriz"]
        if any(p in baixo for p in padroes_lista_aninhada):
            return False

    return True


def carregar_candidatas():
    if DATASET == "humaneval":
        caminho = ARQUIVO_DATASET or CAMINHO_DATASET_HUMANEVAL
        if not os.path.exists(caminho):
            sys.exit(f"ERRO: dataset do HumanEval nao encontrado em '{caminho}'.\n"
                     f"Rode antes:  python baixar_humaneval.py")
        dados = ler_humaneval(caminho)
        candidatas = [e for e in dados if eh_candidata_humaneval(e)]
        print(f"HumanEval: {len(dados)} entradas lidas, {len(candidatas)} passaram no filtro")
        return candidatas[:TAMANHO_LOTE]

    with open(ARQUIVO_DATASET or CAMINHO_DATASET, "r", encoding="utf-8") as f:
        dados = json.load(f)
    candidatas = [e for e in dados if eh_candidata_boa(e)]
    return candidatas[:TAMANHO_LOTE]


# ============================================================
# CONFIGURACAO DO LLM
# ============================================================

def carregar_modelo(modelo_arg=None):
    # Se um modelo foi passado como argumento de linha de comando, usa ele
    # (permite comparar modelos sem precisar editar o arquivo de config)
    if modelo_arg:
        return modelo_arg

    with open(CAMINHO_CONFIG_OLLAMA, "r", encoding="utf-8") as f:
        config = json.load(f)
    # O campo "model" fica aninhado dentro de "json", nao na raiz do arquivo
    return config.get("json", {}).get("model", "qwen2.5-coder:7b")


def nome_seguro_modelo(modelo):
    """Converte o nome do modelo em algo seguro para usar em nomes de arquivo/pasta."""
    return re.sub(r'[^\w\-.]', '_', modelo)


def carregar_guia(com_ponteiros=False):
    if os.path.exists(CAMINHO_GUIA):
        with open(CAMINHO_GUIA, "r", encoding="utf-8") as f:
            guia = f.read()
    else:
        guia = "(guia nao encontrado - traduza seguindo boas praticas de C)"

    if com_ponteiros:
        # Se a opcao foi pedida mas o arquivo nao existe, para com erro claro
        # em vez de rodar silenciosamente sem a secao (o que invalidaria o A/B)
        if not os.path.exists(CAMINHO_GUIA_PONTEIROS):
            sys.exit(f"ERRO: --ponteiros foi pedido, mas '{CAMINHO_GUIA_PONTEIROS}' "
                     f"nao foi encontrado na pasta atual.")
        with open(CAMINHO_GUIA_PONTEIROS, "r", encoding="utf-8") as f:
            guia += "\n\n---\n\n" + f.read()

    return guia


# ============================================================
# ETAPA 1: GENERATION (montar prompt e chamar o LLM)
# ============================================================

def montar_prompt_inicial(entrada, guia_texto):
    codigo = entrada["original_code"]
    testes = "\n\n".join(entrada.get("test", []))

    # So o HumanEval informa o nome da funcao principal; no BigCodeBench
    # o prompt continua exatamente igual ao de antes (para comparar resultados)
    ponto = entrada.get("metadata", {}).get("entry_point")
    dica = ""
    if ponto:
        dica = (f"\nA funcao principal a traduzir se chama `{ponto}`; mantenha esse "
                f"nome em C, EXCETO se ele for igual ao de uma funcao da biblioteca "
                f"padrao do C (ex.: strlen, abs, round, index): nesse caso, use o "
                f"nome com sufixo `_c` (ex.: `{ponto}_c`) na definicao e nos testes, "
                f"pois reutilizar o nome da biblioteca causa erro de compilacao. "
                f"Funcoes auxiliares definidas no codigo Python tambem devem ser "
                f"traduzidas.\n")

    prompt = f"""Voce e um tradutor de codigo Python para C, seguindo ESTRITAMENTE
as regras abaixo (extraidas de um guia validado em 15 traducoes anteriores):

{guia_texto}

TAREFA: Traduza a funcao Python abaixo para C, e traduza tambem os testes
reais fornecidos (NAO invente novos testes). Se algum teste depender de
random, numpy, Faker, ou checar apenas tipo (isinstance), OMITA esse teste
especifico e explique o motivo em um comentario no codigo.
{dica}
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
6. Todo teste DEVE usar assert() (ja incluido, via assert.h) para comparar o
   resultado da funcao com o valor esperado, de modo que o programa ABORTE se
   o resultado estiver errado. NUNCA escreva testes que apenas imprimem o
   resultado com printf, nem funcoes de teste que so devolvem 0/1 sem que o
   main() verifique e aborte: um teste que nao falha quando a funcao esta
   errada e invalido. Para numeros reais use assert(fabs(a - b) < 1e-6).

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

def problema_nos_testes(codigo):
    """Devolve uma mensagem de erro se os testes nao puderem falhar (testes
    'vazios', que so imprimem o resultado), ou None se estiverem ok.
    Sem isso, um programa que apenas imprime 'Test 1 failed' e termina com
    codigo 0 seria contado como sucesso mesmo com a funcao errada."""
    sem_comentarios = re.sub(r"/\*.*?\*/|//[^\n]*", "", codigo, flags=re.DOTALL)
    if "NDEBUG" in sem_comentarios:
        return ("ERRO: nao defina NDEBUG: isso desliga os assert() e invalida os testes.")
    if not re.search(r"\bassert\s*\(", sem_comentarios):
        return ("ERRO: os testes nao sao validos. O programa precisa conter testes que "
                "usam assert(...) para comparar o resultado da funcao com o valor esperado "
                "e que ABORTAM se o resultado estiver errado. Nao use apenas printf, nem "
                "funcoes de teste que so devolvem 0/1. Reescreva os testes com assert().")
    return None


def saida_indica_falha(saida):
    """True se o programa imprimiu uma mensagem de falha (mesmo saindo com codigo 0)."""
    return re.search(r"fail|falh", saida, re.IGNORECASE) is not None


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

    erro_testes = problema_nos_testes(codigo_limpo)
    if erro_testes:
        return False, erro_testes

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

    saida_total = resultado_execucao.stdout + resultado_execucao.stderr
    if saida_indica_falha(saida_total):
        return False, (
            "ERRO: o programa terminou com codigo 0, mas imprimiu uma mensagem de "
            "falha (um teste falhou sem abortar):\n" + saida_total + "\n"
            "Corrija a funcao e use assert() nos testes, para o programa abortar "
            "quando um teste falhar."
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

    # Esgotou as tentativas -> descarta (ou, com --guardar-falhas, guarda o
    # ultimo codigo gerado e o erro numa pasta <ID>_FALHA para analise)
    shutil.rmtree(pasta_trabalho, ignore_errors=True)
    if GUARDAR_FALHAS:
        pasta_falha = pasta_trabalho + "_FALHA"
        shutil.rmtree(pasta_falha, ignore_errors=True)
        os.makedirs(pasta_falha, exist_ok=True)
        with open(os.path.join(pasta_falha, "funcao.py"), "w", encoding="utf-8") as f:
            f.write(entrada["original_code"])
        if codigo_programa:
            with open(os.path.join(pasta_falha, "programa.c"), "w", encoding="utf-8") as f:
                f.write(codigo_programa)
        with open(os.path.join(pasta_falha, "erro.txt"), "w", encoding="utf-8") as f:
            f.write(str(saida_ou_erro))
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


def ler_argumentos():
    parser = argparse.ArgumentParser(description="Pipeline Python -> C (BigCodeBench)")
    parser.add_argument("modelo", nargs="?", default=None,
                        help="modelo do Ollama (padrao: o do ollama_config_local.json)")
    parser.add_argument("--ponteiros", action="store_true",
                        help="anexa guia_ponteiros.md ao guia")
    parser.add_argument("--incluir-aninhadas", action="store_true",
                        help="desliga o filtro de listas aninhadas/matrizes")
    parser.add_argument("--lote", type=int, default=TAMANHO_LOTE,
                        help=f"quantas entradas processar (padrao: {TAMANHO_LOTE})")
    parser.add_argument("--dataset", choices=["bigcodebench", "humaneval"],
                        default="bigcodebench",
                        help="qual conjunto de problemas traduzir (padrao: bigcodebench)")
    parser.add_argument("--arquivo", default=None,
                        help="caminho do arquivo de dataset (padrao: o do dataset escolhido)")
    parser.add_argument("--guardar-falhas", action="store_true",
                        help="guarda o ultimo codigo e o erro das entradas descartadas em <ID>_FALHA/")
    return parser.parse_args()


def main():
    global PASTA_SAIDA, RELATORIO_SAIDA, TAMANHO_LOTE, INCLUIR_ANINHADAS
    global DATASET, ARQUIVO_DATASET, GUARDAR_FALHAS

    args = ler_argumentos()
    TAMANHO_LOTE = args.lote
    INCLUIR_ANINHADAS = args.incluir_aninhadas
    DATASET = args.dataset
    ARQUIVO_DATASET = args.arquivo
    GUARDAR_FALHAS = args.guardar_falhas

    print("Carregando modelo, guia e candidatas...")
    modelo = carregar_modelo(args.modelo)
    guia_texto = carregar_guia(com_ponteiros=args.ponteiros)
    candidatas = carregar_candidatas()
    if not candidatas:
        sys.exit("ERRO: nenhuma entrada passou no filtro de candidatas.")

    # Nomeia a saida com base no modelo e nas opcoes, para poder comparar
    # varias execucoes sem que uma sobrescreva o resultado da outra
    sufixo = nome_seguro_modelo(modelo)
    if args.dataset == "humaneval":
        sufixo += "_humaneval"
    if args.incluir_aninhadas:
        sufixo += "_aninhadas"
    if args.ponteiros:
        sufixo += "_ponteiros"
    PASTA_SAIDA = f"traducoes_automaticas_{sufixo}"
    RELATORIO_SAIDA = f"relatorio_pipeline_{sufixo}.json"

    print(f"Modelo: {modelo}")
    print(f"Dataset: {args.dataset}")
    print(f"Secao de ponteiros: {'SIM' if args.ponteiros else 'nao'} | "
          f"Filtro de listas aninhadas: {'DESLIGADO' if args.incluir_aninhadas else 'ligado'}")
    print(f"Candidatas selecionadas para este lote: {len(candidatas)}")
    print("IDs: " + ", ".join(c["id"] for c in candidatas) + "\n")

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
