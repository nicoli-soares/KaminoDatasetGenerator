# -*- coding: utf-8 -*-
"""
Script para filtrar um LOTE PILOTO de novas candidatas do BigCodeBench,
para testar o pipeline de tradução automatizada (Semana 5-7).

Diferencas em relacao ao script da Semana 3-4:
- Exclui as 10 funcoes ja traduzidas manualmente (nao repetir no piloto)
- Lista de bibliotecas problematicas ampliada, conforme o guia de traducao
- Pensado para gerar um lote PEQUENO (5-10 candidatas) para o piloto,
  nao o dataset final de 100 entradas

Como usar:
1. Coloque este script na pasta raiz do projeto (KaminoDatasetGenerator)
2. Rode: python filtrar_piloto.py
"""

import json

CAMINHO_JSON = "dataset/bigcodebench_normalized_filtered.json"

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

# Padroes de codigo que indicam dependencia do momento exato de execucao
# (nao-deterministico, mesmo motivo de excluir 'random' e 'Faker')
PADROES_NAO_DETERMINISTICOS = [
    ".now(", "datetime.today(", "time.time(", "time.localtime(",
]

# IDs ja traduzidos manualmente nas Semanas 3-4 - nao repetir no piloto
JA_TRADUZIDAS = {
    "BigCodeBench/4", "BigCodeBench/297", "BigCodeBench/254",
    "BigCodeBench/270", "BigCodeBench/97", "BigCodeBench/172",
    "BigCodeBench/178", "BigCodeBench/358", "BigCodeBench/7",
    "BigCodeBench/96",
}

MAX_LINHAS_CODIGO = 15
TAMANHO_LOTE_PILOTO = 12  # quantidade de candidatas a devolver


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

    # Exclui funcoes que dependem do momento exato de execucao (nao-deterministico)
    if any(padrao in codigo for padrao in PADROES_NAO_DETERMINISTICOS):
        return False

    # Evita funcoes com classes internas (padrao OO, fora do escopo do projeto)
    if "class " in codigo:
        return False

    return True


def main():
    with open(CAMINHO_JSON, "r", encoding="utf-8") as f:
        dados = json.load(f)

    candidatas = [e for e in dados if eh_candidata_boa(e)]

    print(f"Total de entradas no dataset: {len(dados)}")
    print(f"Candidatas boas encontradas (excluindo as 10 ja traduzidas): {len(candidatas)}")
    print(f"Mostrando as primeiras {TAMANHO_LOTE_PILOTO} para o piloto:\n")
    print("=" * 70)

    for entrada in candidatas[:TAMANHO_LOTE_PILOTO]:
        print(f"\nID: {entrada['id']}")
        print(f"Descricao: {entrada.get('description', '')[:150]}")
        print(f"Libs: {entrada.get('metadata', {}).get('libs', '[]')}")
        print("-" * 70)
        print(entrada["original_code"])
        print("=" * 70)


if __name__ == "__main__":
    main()
