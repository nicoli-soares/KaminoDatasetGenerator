#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estruturas e tipos necessários
typedef struct {
    const int *input;
    size_t len;
    int delimiter;
} IntersperseInput;

// Função principal traduzida
int* intersperse(const int* numbers, size_t len, int delimiter, size_t* out_len) {
    if (len == 0) {
        *out_len = 0;
        return NULL;  // Representa lista vazia
    }
    *out_len = 2 * len - 1;
    int* result = (int*)malloc(*out_len * sizeof(int));
    size_t idx = 0;
    for (size_t i = 0; i < len - 1; ++i) {
        result[idx++] = numbers[i];
        result[idx++] = delimiter;
    }
    result[idx++] = numbers[len - 1];
    return result;
}

// Função auxiliar para comparar arrays inteiros
bool arrays_equal(const int* a, const int* b, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// Testes
void test_intersperse() {
    // Teste 1: lista vazia
    size_t out_len;
    int* res = intersperse(NULL, 0, 7, &out_len);
    assert(out_len == 0);
    assert(res == NULL);

    // Teste 2: lista com vários elementos
    int input2[] = {5, 6, 3, 2};
    int expected2[] = {5, 8, 6, 8, 3, 8, 2};
    size_t out_len2;
    int* res2 = intersperse(input2, 4, 8, &out_len2);
    assert(out_len2 == 7);
    assert(arrays_equal(res2, expected2, out_len2));
    free(res2);

    // Teste 3: lista com elementos repetidos
    int input3[] = {2, 2, 2};
    int expected3[] = {2, 2, 2, 2, 2};
    size_t out_len3;
    int* res3 = intersperse(input3, 3, 2, &out_len3);
    assert(out_len3 == 5);
    assert(arrays_equal(res3, expected3, out_len3));
    free(res3);
}

// Função main que executa os testes
int main(void) {
    test_intersperse();
    return 0;
}