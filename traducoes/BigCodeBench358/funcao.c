#include <stdio.h>
#include <string.h>
#define MAX_ELEMENTO 32
#define MAX_ELEMENTOS 32
#define MAX_R 10

typedef struct {
    char valores[MAX_R][MAX_ELEMENTO];
} Combinacao;

// Extrai os elementos de um array JSON (numeros ou strings) associado a uma chave
// Retorna 1 se encontrou e conseguiu parsear, 0 caso contrario
static int extrair_lista(const char *json_data, const char *chave,
                          char elementos[][MAX_ELEMENTO], int *n) {
    char busca[64];
    snprintf(busca, sizeof(busca), "\"%s\"", chave);

    const char *pos = strstr(json_data, busca);
    if (!pos) return 0;

    pos = strchr(pos, ':');
    if (!pos) return 0;
    pos++;
    while (*pos == ' ') pos++;
    if (*pos != '[') return 0;
    pos++;

    *n = 0;
    while (*pos != ']' && *pos != '\0') {
        while (*pos == ' ' || *pos == ',') pos++;
        if (*pos == ']') break;

        char valor[MAX_ELEMENTO];
        int i = 0;
        if (*pos == '"') {
            pos++;
            while (*pos != '"' && *pos != '\0' && i < MAX_ELEMENTO - 1) {
                valor[i++] = *pos++;
            }
            if (*pos == '"') pos++;
        } else {
            while (*pos != ',' && *pos != ']' && *pos != '\0' && i < MAX_ELEMENTO - 1) {
                valor[i++] = *pos++;
            }
        }
        valor[i] = '\0';

        if (*n < MAX_ELEMENTOS) {
            strcpy(elementos[*n], valor);
            (*n)++;
        }
    }
    return 1;
}

// Gera recursivamente as combinacoes de tamanho r (mesma logica da BigCodeBench/297,
// mas operando sobre strings genericas em vez de numeros)
static void gerar_combinacoes(char elementos[][MAX_ELEMENTO], int n, int r, char atual[][MAX_ELEMENTO], int pos_atual, int inicio, Combinacao *resultado, int *num_combinacoes) {
    int i;
    if (pos_atual == r) {
        for (i = 0; i < r; i++) {
            strcpy(resultado[*num_combinacoes].valores[i], atual[i]);
        }
        (*num_combinacoes)++;
        return;
    }

    for (i = inicio; i < n; i++) {
        strcpy(atual[pos_atual], elementos[i]);
        gerar_combinacoes(elementos, n, r, atual, pos_atual + 1, i + 1, resultado, num_combinacoes);
    }
}

// Funcao principal - equivalente ao task_func do Python
int task_func(const char *json_list, int r, Combinacao *resultado, int *num_combinacoes) {
    char elementos[MAX_ELEMENTOS][MAX_ELEMENTO];
    int n;

    if (!extrair_lista(json_list, "number_list", elementos, &n)) {
        return -1;
    }

    char atual[MAX_R][MAX_ELEMENTO];
    *num_combinacoes = 0;

    gerar_combinacoes(elementos, n, r, atual, 0, 0, resultado, num_combinacoes);

    return 0;
}