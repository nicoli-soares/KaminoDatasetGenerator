# -*- coding: utf-8 -*-
"""
Baixa o HumanEval (164 problemas) e salva em dataset/humaneval.jsonl,
o arquivo que o pipeline le com:  --dataset humaneval

Uso (na pasta do projeto, no servidor ou no notebook):
  python baixar_humaneval.py

Tenta primeiro a API do Hugging Face (openai/openai_humaneval) e, se falhar,
o arquivo original do GitHub (openai/human-eval). So usa a biblioteca padrao
do Python (nao precisa instalar nada).

Se a maquina nao tiver acesso a nenhum dos dois, rode este script no notebook
e copie o arquivo gerado para o servidor:
  scp dataset/humaneval.jsonl kamino@100.80.103.98:~/projetos/KaminoC/dataset/
"""

import gzip
import json
import os
import sys
import urllib.parse
import urllib.request

SAIDA = "dataset/humaneval.jsonl"
CAMPOS = ["task_id", "prompt", "canonical_solution", "test", "entry_point"]
TOTAL_ESPERADO = 164

URL_API = "https://datasets-server.huggingface.co/rows"
URL_GITHUB = "https://github.com/openai/human-eval/raw/master/data/HumanEval.jsonl.gz"


def baixar_pela_api():
    linhas = []
    offset = 0
    total = None
    while total is None or offset < total:
        params = urllib.parse.urlencode({
            "dataset": "openai/openai_humaneval",
            "config": "openai_humaneval",
            "split": "test",
            "offset": offset,
            "length": 100,
        })
        with urllib.request.urlopen(f"{URL_API}?{params}", timeout=60) as resposta:
            dados = json.load(resposta)
        total = dados["num_rows_total"]
        itens = dados["rows"]
        if not itens:
            break
        for item in itens:
            if item.get("truncated_cells"):
                raise ValueError("a API devolveu campos truncados")
            linhas.append(item["row"])
        offset += len(itens)
    return linhas


def baixar_pelo_github():
    with urllib.request.urlopen(URL_GITHUB, timeout=60) as resposta:
        texto = gzip.decompress(resposta.read()).decode("utf-8")
    return [json.loads(l) for l in texto.splitlines() if l.strip()]


def validar(linhas):
    if len(linhas) != TOTAL_ESPERADO:
        raise ValueError(f"esperava {TOTAL_ESPERADO} problemas, vieram {len(linhas)}")
    for linha in linhas:
        faltando = [c for c in CAMPOS if c not in linha or not isinstance(linha[c], str)]
        if faltando:
            raise ValueError(f"{linha.get('task_id', '?')}: campos ausentes {faltando}")


def main():
    linhas = None
    for nome, funcao in (("API do Hugging Face", baixar_pela_api),
                         ("GitHub (openai/human-eval)", baixar_pelo_github)):
        try:
            print(f"Baixando de: {nome}...")
            candidatas = funcao()
            validar(candidatas)
            linhas = candidatas
            break
        except Exception as erro:
            print(f"  nao deu certo: {erro}")

    if linhas is None:
        sys.exit("ERRO: nao consegui baixar o HumanEval por nenhum caminho.\n"
                 "Rode este script em outra maquina com internet e copie o arquivo "
                 f"'{SAIDA}' para esta pasta.")

    os.makedirs(os.path.dirname(SAIDA), exist_ok=True)
    with open(SAIDA, "w", encoding="utf-8") as f:
        for linha in linhas:
            f.write(json.dumps({c: linha[c] for c in CAMPOS}, ensure_ascii=False) + "\n")

    print(f"OK: {len(linhas)} problemas salvos em {SAIDA}")


if __name__ == "__main__":
    main()
