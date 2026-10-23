#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// ---------- Mapeamento de palavras para valores numéricos ----------
typedef struct {
    const char *palavra;
    int valor;
} MapeamentoNumero;

static const MapeamentoNumero MAPEAMENTO_NUMERO[10] = {
    {"zero",   0},
    {"one",    1},
    {"two",    2},
    {"three",  3},
    {"four",   4},
    {"five",   5},
    {"six",    6},
    {"seven",  7},
    {"eight",  8},
    {"nine",   9}
};

// ---------- Função auxiliar: converte palavra em valor ----------
static int obter_valor(const char *palavra) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(palavra, MAPEAMENTO_NUMERO[i].palavra) == 0) {
            return MAPEAMENTO_NUMERO[i].valor;
        }
    }
    return -1; // não esperado
}

// ---------- Função principal ----------
char *sort_numbers(const char *numbers) {
    if (numbers == NULL || *numbers == '\0') {
        char *res = (char *)malloc(1);
        if (res) res[0] = '\0';
        return res;
    }

    size_t len = strlen(numbers);
    char *buf = (char *)malloc(len + 1);
    if (!buf) return NULL;
    strcpy(buf, numbers);

    // Máximo possível de tokens (cada token mínimo de 1 caractere + espaço)
    const int MAX_TOKENS = 256;
    const char *tokens[MAX_TOKENS];
    int count = 0;

    char *token = strtok(buf, " ");
    while (token && count < MAX_TOKENS) {
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }

    // Ordenação por valor numérico (insertion sort simples)
    for (int i = 1; i < count; i++) {
        const char *key = tokens[i];
        int key_val = obter_valor(key);
        int j = i - 1;
        while (j >= 0 && obter_valor(tokens[j]) > key_val) {
            tokens[j + 1] = tokens[j];
            j--;
        }
        tokens[j + 1] = key;
    }

    // Construir string resultante
    size_t out_len = 0;
    for (int i = 0; i < count; i++) {
        out_len += strlen(tokens[i]);
    }
    out_len += (count > 0) ? (count - 1) : 0; // espaços

    char *out = (char *)malloc(out_len + 1);
    if (!out) {
        free(buf);
        return NULL;
    }

    char *p = out;
    for (int i = 0; i < count; i++) {
        size_t l = strlen(tokens[i]);
        memcpy(p, tokens[i], l);
        p += l;
        if (i != count - 1) {
            *p++ = ' ';
        }
    }
    *p = '\0';

    free(buf);
    return out;
}

// ---------- Testes ----------
static void test_sort_numbers(void) {
    // Teste 1: string vazia
    char *res1 = sort_numbers("");
    assert(strcmp(res1, "") == 0);
    free(res1);

    // Teste 2: único número
    char *res2 = sort_numbers("three");
    assert(strcmp(res2, "three") == 0);
    free(res2);

    // Teste 3: já ordenado
    char *res3 = sort_numbers("three five nine");
    assert(strcmp(res3, "three five nine") == 0);
    free(res3);

    // Teste 4: mistura
    char *res4 = sort_numbers("five zero four seven nine eight");
    assert(strcmp(res4, "zero four five seven eight nine") == 0);
    free(res4);

    // Teste 5: ordem inversa
    char *res5 = sort_numbers("six five four three two one zero");
    assert(strcmp(res5, "zero one two three four five six") == 0);
    free(res5);
}

// ---------- Entry Point ----------
int main(void) {
    test_sort_numbers();
    return 0;
}