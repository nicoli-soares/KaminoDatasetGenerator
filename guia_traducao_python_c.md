# Guia de Tradução: BigCodeBench (Python) → C
### Consolidado a partir de 10 traduções manuais validadas (Semanas 3-4)

Este documento resume as decisões de design e padrões de tradução usados nas 10
funções já traduzidas manualmente. Ele serve como referência para orientar a
tradução automatizada (via LLM) nas Semanas 5-7, garantindo consistência entre
as traduções feitas na mão e as geradas automaticamente.

---

## 1. Regras gerais de tradução

### 1.1. Sem dicionário nativo → array de structs
Toda vez que o código Python usa `dict`, `Counter`, ou `defaultdict`, a tradução em C
deve usar um **array de structs** contendo (chave, valor), com busca linear para
verificar se a chave já existe.

```c
typedef struct {
    <tipo_da_chave> chave;
    <tipo_do_valor> valor;
} ParChaveValor;
```

- Se a chave é numérica, comparar com `==`.
- Se a chave é texto, comparar com `strcmp()`.
- Se a lista pode conter tanto números quanto texto (Python é dinamicamente
  tipado), representar TODOS os elementos como string internamente, convertendo
  números com `snprintf`/`sprintf` quando necessário.

### 1.2. Sem exceções → códigos de retorno
C não tem `try/except`. Toda função que pode falhar deve seguir este padrão:
- Retornar `int` como código de status: `0` = sucesso, valores negativos = tipos
  diferentes de erro (cada erro do Python deve virar um código diferente,
  ex: `-1` para arquivo não encontrado, `-2` para dado ausente, `-3` para
  conversão inválida).
- O resultado de verdade é escrito em um parâmetro de saída (ponteiro),
  passado por referência.
- Se o Python **relança** a exceção (`raise e`) → replicar com retorno de erro
  simples (a função "falha" do ponto de vista de quem chama).
- Se o Python **captura e converte em texto** (`except: return str(e)`) → a
  função em C nunca "falha" tecnicamente; ela sempre escreve algum resultado
  (a mensagem de erro como se fosse um resultado válido).

### 1.3. Sem `itertools.combinations` → recursão com backtracking
Sempre que o Python usa `itertools.combinations`, implementar com uma função
recursiva auxiliar que constrói a combinação elemento por elemento, avançando
um índice de início para evitar repetições.

### 1.4. Sem biblioteca JSON → extração manual de campos
Não usar bibliotecas JSON externas. Para os casos deste dataset (JSON "plano",
poucos campos), extrair valores manualmente:
- Localizar a chave com `strstr()`.
- Avançar até depois do `:`.
- Se o valor é uma string, capturar o conteúdo entre aspas.
- Se o valor é um array `[...]`, iterar item por item, separando por vírgula.

### 1.5. Sem `random`/`Faker` → excluir da amostra
Funções ou testes que dependem de números aleatórios não-determinísticos
(`random`, `numpy.random`, `Faker`, etc.) devem ser **descartados** do lote de
tradução. Não vale a pena tentar traduzir; o LLM deve pular esses casos.
(Esse filtro já deve acontecer ANTES da tradução, na etapa de seleção de
candidatas.)

### 1.5b. Sem dependência do momento atual de execução → mesma exclusão
Funções que chamam `datetime.now()`, `datetime.today()`, `time.time()`, etc.
sofrem do mesmo problema do `random`: o resultado muda a cada execução
(hoje é diferente de amanhã), então não é possível escrever um teste com
resultado fixo. Excluir da amostra pelo mesmo motivo.

### 1.5c. Sem introspecção de código (`inspect`, `types`) → impossível de traduzir
Funções que examinam outras funções em tempo de execução (parâmetros, se é
lambda, anotações, etc., via o módulo `inspect`) não têm equivalente em C.
C é compilado e estaticamente tipado — não existe reflexão/introspecção de
código da forma como Python permite. Excluir sempre que aparecer `inspect`
ou `types.LambdaType` no código.

### 1.6. Sem overflow automático → cuidado com tipos numéricos
Python tem inteiros de precisão arbitrária; C não. Ao traduzir operações que
envolvem produtos ou somas de múltiplos números, preferir `long long` a `int`
para reduzir risco de overflow.

### 1.7. Sem checagem de tipo em runtime → simplificar/omitir testes de tipo
Testes Python que checam `isinstance(resultado, float)`, `isinstance(resultado, list)`,
etc., não têm equivalente útil em C (o tipo já é garantido em tempo de
compilação). Esses testes devem ser omitidos, com uma nota explicando o motivo.

### 1.8. Bibliotecas de sistema (`time.h`) devem ser evitadas quando afetam
reprodutibilidade. Preferir implementações matemáticas puras (ex: algoritmo de
Sakamoto para dia da semana) em vez de funções que dependem de configuração do
sistema operacional (fuso horário, locale).

---

### 1.9. Regex com múltiplas alternativas → validar contra os testes reais, não só ler o padrão
Padrões regex com várias alternativas (`|`) podem ter alternativas que **nunca
disparam de verdade** dado o formato real dos dados de entrada, mesmo que
pareçam relevantes só de ler a expressão. Antes de implementar uma tradução
literal e completa de um regex complexo, trace manualmente o comportamento do
padrão contra os testes reais fornecidos — a versão mais simples que ainda
reproduz todos os testes é preferível a uma tradução literal desnecessariamente
complexa. Documentar SEMPRE essa simplificação como uma limitação conhecida
(ela pode divergir do regex original em entradas fora do que foi testado).

## 2. Bibliotecas Python a EXCLUIR já na filtragem de candidatas

Funções que importam qualquer uma destas bibliotecas devem ser descartadas
antes mesmo de tentar traduzir:

```
random, numpy, pandas, os, unittest.mock, statistics, sklearn, matplotlib,
scipy, requests, flask, flask_restful, django, urllib, socket, bs4, http,
smtplib, ftplib, psutil, platform, subprocess, shutil, multiprocessing,
threading, zlib, gzip, cryptography, hashlib, zipfile, struct, pickle,
sqlite3, sqlalchemy, ipaddress, nltk, faker, geopy, folium, docx, glob,
xmltodict, prettytable, unicodedata, pytz, inspect, types, yaml, dateutil
```

## 3. Testes a excluir (mesmo em funções aceitas)

Dentro de uma função aceita, testes individuais que usam Faker, random, ou que
checam apenas tipo (`isinstance`) devem ser omitidos da tradução, com uma nota
indicando o motivo. Isso NÃO invalida a função inteira — só aquele teste
específico.

---

## 4. Limitações conhecidas e aceitas (documentar, não resolver)

- Arrays de resultado com tamanho fixo (tipicamente 100-1000 posições) — sem
  alocação dinâmica ilimitada.
- Busca linear O(n²) em vez de hash table O(n) — aceitável para o volume do
  dataset.
- Parsing de CSV/JSON manual e frágil — não lida com casos avançados (aspas
  escapadas, valores com vírgula dentro de aspas, etc.).
- Nomes de produtos/palavras limitados a um tamanho máximo de string
  (tipicamente 128-256 caracteres).

---

## 5. Checklist para cada nova tradução automatizada

Antes de aceitar uma tradução gerada pelo LLM como válida, confirmar:

- [ ] Compila sem erros (`gcc -o teste teste.c` ou com `-lm` se usar `math.h`)
- [ ] Todos os testes reais traduzidos do campo `"test"` do JSON passam
- [ ] Testes que dependem de random/Faker foram corretamente omitidos (não
      forçados a virar determinísticos de forma incorreta)
- [ ] Testes de tipo (`isinstance`) foram omitidos ou adaptados corretamente
- [ ] Casos de erro (arquivo ausente, chave ausente, conversão inválida) usam
      código de retorno, não travam o programa
- [ ] Sem vazamento de memória óbvio (todo `malloc` tem `free` correspondente)

---

## 6. Formato de prompt sugerido para o LLM (rascunho)

```
Você é um tradutor de código Python para C, seguindo estas regras estritas:
[colar as seções 1 e 2 deste documento]

Traduza a função Python abaixo para C, e traduza também os testes reais
fornecidos (não invente novos testes). Se algum teste depender de random,
numpy ou Faker, omita-o e explique o motivo em um comentário.

Código Python:
<<<original_code>>>

Testes Python:
<<<test>>>

Responda com dois blocos de código: a função em C, e os testes em C.
```

Este formato de prompt deve ser refinado durante o piloto (Fase 1), com base
nos erros observados nas primeiras tentativas automatizadas.
