## 7. Ponteiros e memória em C: padrões seguros (leia antes de escrever qualquer código com ponteiros)

Os erros mais comuns de tradução Python → C vêm de ponteiros e memória, não da lógica.
Siga SEMPRE estes padrões. Eles foram escolhidos para evitar os erros reais já observados.

**Regras de ouro**
1. Prefira arrays de tamanho fixo e índices inteiros. Evite `malloc` sempre que o tamanho máximo for conhecido.
2. Toda função que recebe um array recebe TAMBÉM o tamanho dele (`int n`, `size_t tam`).
3. NUNCA use `int **` ou `int ***` para representar listas ou matrizes. Use os padrões 2 e 4 abaixo.
4. NUNCA passe `&array` para uma função: passe `array` (o nome do array já é o ponteiro).
5. Toda string em C termina em `'\0'`, e o buffer precisa ter espaço para ele.

---

### Padrão 1: passar um array para uma função (sem `&`)

ERRADO (o `&` muda o tipo e causa erro de compilação):
```c
int v[] = {1, 2, 3};
int r = soma_array(&v, 3);   /* tipo errado: int (*)[3] em vez de int * */
```

CERTO:
```c
int soma_array(const int *valores, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += valores[i];
    }
    return total;
}
/* uso: */
int v[] = {1, 2, 3, 4};
int r = soma_array(v, 4);    /* sem &, com o tamanho */
```

### Padrão 2: lista de listas / matriz → array plano (NUNCA `int **`)

ERRADO: `int **m`, `int ***lista`, `(int **)&matriz`. Cada nível extra de `*` é uma fonte de erro.

CERTO: um único array, com o elemento (i, j) em `m[i * colunas + j]`:
```c
int soma_matriz(const int *m, int linhas, int colunas) {
    int total = 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            total += m[i * colunas + j];
        }
    }
    return total;
}
/* uso, com a matriz declarada no teste: */
int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
int r = soma_matriz(&m[0][0], 2, 3);   /* ponteiro para o primeiro elemento */
```

### Padrão 3: devolver texto → buffer fornecido por quem chama

ERRADO: devolver `char *` apontando para uma variável local (ela deixa de existir quando a função termina), ou escrever sem checar o tamanho.

CERTO: quem chama fornece o buffer e o tamanho; a função usa `snprintf` (que sempre termina a string) e devolve um código de status:
```c
int formatar_par(int a, int b, char *saida, size_t tam_saida) {
    int escritos = snprintf(saida, tam_saida, "(%d, %d)", a, b);
    if (escritos < 0 || (size_t)escritos >= tam_saida) {
        return -1;   /* buffer pequeno demais */
    }
    return 0;
}
/* uso: */
char buf[32];
int status = formatar_par(3, 7, buf, sizeof(buf));
```
Evite `strncpy` para copiar texto: ele NÃO coloca o `'\0'` quando o texto original é maior que o limite. Prefira `snprintf(destino, tam, "%s", origem)`.

### Padrão 4: lista de textos → array 2D de tamanho fixo (NUNCA `char **`)

CERTO:
```c
#define MAX_TEXTO 64
int contar_palavra(const char palavras[][MAX_TEXTO], int n, const char *alvo) {
    int contagem = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(palavras[i], alvo) == 0) {
            contagem++;
        }
    }
    return contagem;
}
/* uso: */
char palavras[3][MAX_TEXTO] = {"gato", "cao", "gato"};
int r = contar_palavra(palavras, 3, "gato");
```

### Padrão 5: quando `malloc` for inevitável

Regras: (a) sempre checar `NULL`; (b) liberar com `free` na mesma função que alocou; (c) alocar `tamanho + 1` para strings; (d) nunca usar a memória depois do `free`.
```c
int copiar_maiusculo(const char *origem, char *saida, size_t tam_saida) {
    size_t n = strlen(origem);
    char *temp = (char *)malloc(n + 1);
    if (temp == NULL) {
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        temp[i] = (char)toupper((unsigned char)origem[i]);
    }
    temp[n] = '\0';
    int status = 0;
    if (n + 1 > tam_saida) {
        status = -2;
    } else {
        memcpy(saida, temp, n + 1);
    }
    free(temp);          /* liberado antes de todo return, exceto o de NULL acima */
    return status;
}
```

### Padrão 6: manipular bytes ou bits (base64, hex, etc.) → use ÍNDICES inteiros

ERRADO: fazer conta com ponteiros (`8 * (ponteiro - outro_ponteiro)`, `resultado - out`). Misturar ponteiro com inteiro nas contas gera erro de compilação ou de memória.

CERTO: guardar a posição em uma variável inteira e usar `saida[pos]`:
```c
int duplicar_bytes(const unsigned char *entrada, int n, unsigned char *saida, int cap_saida) {
    int pos_saida = 0;
    for (int i = 0; i < n; i++) {
        if (pos_saida + 2 > cap_saida) {
            return -1;               /* sem espaço: erro, nunca escrever além do limite */
        }
        saida[pos_saida++] = entrada[i];
        saida[pos_saida++] = entrada[i];
    }
    return pos_saida;                /* quantidade de bytes escritos */
}
```

**Antes de responder, confira:** nenhum `int **`/`int ***`; nenhum `&array` passado a função; todo buffer tem tamanho conhecido e é respeitado; toda string termina em `'\0'`; todo `malloc` tem `free`.
