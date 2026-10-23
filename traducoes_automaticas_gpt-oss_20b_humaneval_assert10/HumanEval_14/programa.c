#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estruturas e funções auxiliares -----------------------------------------

// Calcula o tamanho de uma string (não usa strlen da biblioteca padrão)
static size_t string_len(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') len++;
    return len;
}

// Função que gera todos os prefixos de uma string
// Retorna um array de strings (char**) e coloca o tamanho em *out_len
char **all_prefixes(const char *string, int *out_len) {
    size_t len = string_len(string);
    if (len == 0) {
        *out_len = 0;
        return NULL;
    }
    // Aloca array de ponteiros para cada prefixo
    char **prefixes = (char **)malloc(len * sizeof(char *));
    if (!prefixes) {
        *out_len = 0;
        return NULL;
    }
    for (size_t i = 0; i < len; ++i) {
        // Cada prefixo tem tamanho i+1 + terminador nulo
        prefixes[i] = (char *)malloc((i + 2) * sizeof(char));
        if (!prefixes[i]) {
            // Libera já alocado antes de falhar
            for (size_t j = 0; j < i; ++j) free(prefixes[j]);
            free(prefixes);
            *out_len = 0;
            return NULL;
        }
        // Copia os primeiros i+1 caracteres
        for (size_t k = 0; k < i + 1; ++k) {
            prefixes[i][k] = string[k];
        }
        prefixes[i][i + 1] = '\0';
    }
    *out_len = (int)len;
    return prefixes;
}

// Compara dois arrays de strings; retorna true se iguais
static bool arrays_equal(const char **a, int len_a, const char **b, int len_b) {
    if (len_a != len_b) return false;
    for (int i = 0; i < len_a; ++i) {
        if (string_len(a[i]) != string_len(b[i])) return false;
        for (size_t j = 0; j < string_len(a[i]); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Libera memória alocada por all_prefixes
static void free_prefixes(char **prefixes, int len) {
    if (!prefixes) return;
    for (int i = 0; i < len; ++i) free(prefixes[i]);
    free(prefixes);
}

// Testes ---------------------------------------------------------

void test_empty() {
    int len = 0;
    char **result = all_prefixes("", &len);
    assert(result == NULL);
    assert(len == 0);
    // Não há memória a liberar
}

void test_asdfgh() {
    const char *expected_strings[] = {"a","as","asd","asdf","asdfg","asdfgh"};
    int expected_len = 6;
    int len = 0;
    char **result = all_prefixes("asdfgh", &len);
    assert(len == expected_len);
    // Compara conteúdo
    bool ok = arrays_equal((const char **)result, len,
                           (const char **)expected_strings, expected_len);
    assert(ok);
    free_prefixes(result, len);
}

void test_WWW() {
    const char *expected_strings[] = {"W","WW","WWW"};
    int expected_len = 3;
    int len = 0;
    char **result = all_prefixes("WWW", &len);
    assert(len == expected_len);
    bool ok = arrays_equal((const char **)result, len,
                           (const char **)expected_strings, expected_len);
    assert(ok);
    free_prefixes(result, len);
}

// Função main executa os testes ----------------------------------------

int main(void) {
    test_empty();
    test_asdfgh();
    test_WWW();
    return 0;
}