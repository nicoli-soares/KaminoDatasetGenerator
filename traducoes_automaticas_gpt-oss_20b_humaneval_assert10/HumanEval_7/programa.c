#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estrutura para armazenar o resultado da filtragem
typedef struct {
    const char **array;   // ponteiro para os elementos filtrados
    size_t count;         // número de elementos filtrados
} FilterResult;

// Função principal a ser traduzida
FilterResult filter_by_substring(const char **strings, size_t n, const char *substring) {
    FilterResult res = {NULL, 0};
    if (n == 0 || !substring) {
        return res; // devolve vetor vazio
    }

    // Primeiro, conta quantos elementos contêm o substring
    size_t matches = 0;
    for (size_t i = 0; i < n; i++) {
        if (strings[i] && strstr(strings[i], substring)) {
            matches++;
        }
    }

    res.count = matches;
    if (matches == 0) {
        return res; // não há correspondências
    }

    // Aloca vetor de ponteiros para os resultados
    res.array = (const char **)malloc(matches * sizeof(const char *));
    size_t idx = 0;
    for (size_t i = 0; i < n; i++) {
        if (strings[i] && strstr(strings[i], substring)) {
            res.array[idx++] = strings[i];
        }
    }
    return res;
}

// Função auxiliar para comparar dois vetores de strings
void assert_equal_arrays(const char **actual, size_t actual_count,
                         const char **expected, size_t expected_count) {
    assert(actual_count == expected_count);
    for (size_t i = 0; i < actual_count; i++) {
        assert(strcmp(actual[i], expected[i]) == 0);
    }
}

// Funções de teste baseadas nos testes Python originais
void check(void) {
    // Teste 1: lista vazia
    FilterResult res0 = filter_by_substring(NULL, 0, "john");
    assert(res0.count == 0);
    if (res0.array) free(res0.array);

    // Teste 2
    const char *strings2[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    FilterResult res2 = filter_by_substring(strings2, 6, "xxx");
    const char *expected2[] = {"xxx", "xxxAAA", "xxx"};
    assert_equal_arrays(res2.array, res2.count, expected2, 3);
    free(res2.array);

    // Teste 3
    const char *strings3[] = {"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"};
    FilterResult res3 = filter_by_substring(strings3, 6, "xx");
    const char *expected3[] = {"xxx", "aaaxxy", "xxxAAA", "xxx"};
    assert_equal_arrays(res3.array, res3.count, expected3, 4);
    free(res3.array);

    // Teste 4
    const char *strings4[] = {"grunt", "trumpet", "prune", "gruesome"};
    FilterResult res4 = filter_by_substring(strings4, 4, "run");
    const char *expected4[] = {"grunt", "prune"};
    assert_equal_arrays(res4.array, res4.count, expected4, 2);
    free(res4.array);
}

// Função main para executar os testes
int main(void) {
    check();
    return 0;
}