#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Estrutura para armazenar vetor dinâmico de inteiros */
typedef struct {
    int *data;
    size_t size;
} IntVector;

/* Função auxiliar: insere um elemento se ainda não existir no vetor */
static void add_unique(IntVector *vec, int value) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (vec->data[i] == value) {
            return; /* já existe */
        }
    }
    vec->data[vec->size++] = value;
}

/* Função auxiliar: ordena o vetor em ordem crescente (insertion sort) */
static void insertion_sort(IntVector *vec) {
    for (size_t i = 1; i < vec->size; ++i) {
        int key = vec->data[i];
        size_t j = i;
        while (j > 0 && vec->data[j - 1] > key) {
            vec->data[j] = vec->data[j - 1];
            --j;
        }
        vec->data[j] = key;
    }
}

/* Função principal traduzida: unique
 * Parâmetros:
 *   input   - array de inteiros de entrada
 *   n       - tamanho do array de entrada
 *   output  - ponteiro para receber o array resultante (alocado com malloc)
 *   out_size- ponteiro para receber o tamanho do array resultante
 * Retorno: 0 em caso de sucesso, valor negativo em caso de erro
 */
int unique(int *input, size_t n, int **output, size_t *out_size) {
    if (!output || !out_size) {
        return -1; /* parâmetros inválidos */
    }

    /* Vetor temporário para armazenar elementos únicos (máximo n elementos) */
    IntVector vec;
    vec.data = (int *)malloc(n * sizeof(int));
    if (!vec.data) {
        return -2; /* falha de alocação */
    }
    vec.size = 0;

    /* Construir conjunto de elementos únicos */
    for (size_t i = 0; i < n; ++i) {
        add_unique(&vec, input[i]);
    }

    /* Ordenar o vetor resultante */
    insertion_sort(&vec);

    /* Alocar array final com tamanho exato */
    int *res = (int *)malloc(vec.size * sizeof(int));
    if (!res) {
        free(vec.data);
        return -2; /* falha de alocação */
    }
    for (size_t i = 0; i < vec.size; ++i) {
        res[i] = vec.data[i];
    }

    free(vec.data);
    *output = res;
    *out_size = vec.size;
    return 0; /* sucesso */
}

/* Função auxiliar para comparar dois arrays inteiros */
static void assert_arrays_equal(int *a, size_t na, int *b, size_t nb) {
    assert(na == nb);
    for (size_t i = 0; i < na; ++i) {
        assert(a[i] == b[i]);
    }
}

/* Teste 1: verifica comportamento básico com lista de inteiros */
static void test_unique_basic(void) {
    int test_input[] = {5, 3, 5, 2, 3, 3, 9, 0, 123};
    size_t n = sizeof(test_input) / sizeof(test_input[0]);

    int *result = NULL;
    size_t result_size = 0;
    int status = unique(test_input, n, &result, &result_size);
    assert(status == 0);

    int expected[] = {0, 2, 3, 5, 9, 123};
    size_t expected_size = sizeof(expected) / sizeof(expected[0]);

    assert_arrays_equal(result, result_size, expected, expected_size);

    free(result);
}

/* Função main executando todos os testes */
int main(void) {
    test_unique_basic();
    /* Se chegar aqui, todos os testes passaram */
    return 0;
}