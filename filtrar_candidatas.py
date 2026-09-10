# -*- coding: utf-8 -*-
"""
Script para filtrar boas candidatas do BigCodeBench para traduzir manualmente para C.

Critérios de filtro:
1. Não usa 'random' na lógica principal (evita problemas de PRNG diferente entre Python e C)
2. Não depende de bibliotecas pesadas (numpy, pandas, etc.)
3. Não depende do sistema de arquivos/SO de forma complexa (os, mocks)
4. Código relativamente curto (mais fácil de traduzir e validar)
5. Nível de dificuldade "easy" (campo metadata.split)

Como usar:
1. Coloque este script na pasta raiz do projeto (KaminoDatasetGenerator)
2. Ajuste o caminho do arquivo JSON abaixo, se necessário
3. Rode: python filtrar_candidatas.py
"""

import json

# Ajuste esse caminho se necessário
CAMINHO_JSON = "dataset/bigcodebench_normalized_filtered.json"

# Bibliotecas que queremos EVITAR nas primeiras traduções
LIBS_PROBLEMATICAS = {
    "random",       # PRNG diferente entre Python e C
    "numpy",        # biblioteca pesada, sem equivalente direto em C
    "pandas",       # idem
    "os",           # sistema de arquivos, geralmente usa mocks nos testes
    "unittest.mock",
    "statistics",   # tem equivalente, mas adiciona complexidade extra
    "sklearn",
    "matplotlib",
    "scipy",
    # Web / rede
    "requests", "flask", "flask_restful", "django", "urllib", "socket",
    "bs4", "http", "smtplib", "ftplib",
    # Sistema operacional / processos
    "psutil", "platform", "subprocess", "shutil", "multiprocessing",
    "threading",
    # Compressão / criptografia / serialização binária pesada
    "zlib", "gzip", "cryptography", "hashlib", "zipfile", "struct",
    "pickle",
    # Bancos de dados / ORMs
    "sqlite3", "sqlalchemy",
    # Rede de baixo nível
    "ipaddress",
}

# Tamanho máximo de código (em linhas) para ser considerado "simples"
MAX_LINHAS_CODIGO = 15


def eh_candidata_boa(entrada):
    """Retorna True se a entrada passar em todos os critérios."""
    codigo = entrada.get("original_code", "")
    metadata = entrada.get("metadata", {})
    libs_str = metadata.get("libs", "[]")

    # Tenta extrair a lista de libs de forma segura
    try:
        libs = eval(libs_str) if isinstance(libs_str, str) else libs_str
    except Exception:
        libs = []

    # Critério 1: nenhuma lib problemática
    if any(lib in LIBS_PROBLEMATICAS for lib in libs):
        return False

    # Critério 2: nível de dificuldade "easy" (se o campo existir)
    if metadata.get("split") and metadata["split"] != "easy":
        return False

    # Critério 3: código curto
    num_linhas = len([l for l in codigo.split("\n") if l.strip()])
    if num_linhas > MAX_LINHAS_CODIGO:
        return False

    # Critério 4: não usar 'random.' ou 'np.' diretamente no corpo do código
    # (checagem extra, caso a lib não esteja listada em metadata.libs)
    if "random." in codigo or "np." in codigo or "numpy." in codigo:
        return False

    return True


def main():
    with open(CAMINHO_JSON, "r", encoding="utf-8") as f:
        dados = json.load(f)

    candidatas = [e for e in dados if eh_candidata_boa(e)]

    print(f"Total de entradas no dataset: {len(dados)}")
    print(f"Candidatas boas encontradas: {len(candidatas)}\n")
    print("=" * 70)

    for entrada in candidatas[:20]:  # mostra até 20 pra você escolher 10
        print(f"\nID: {entrada['id']}")
        print(f"Descrição: {entrada.get('description', '')[:150]}")
        print(f"Libs: {entrada.get('metadata', {}).get('libs', '[]')}")
        print("-" * 70)
        print(entrada["original_code"])
        print("=" * 70)


if __name__ == "__main__":
    main()
