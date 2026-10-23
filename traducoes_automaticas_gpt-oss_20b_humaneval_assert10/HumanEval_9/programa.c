#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estrutura de resultado opcional para retorno de tamanho
typedef struct {
    int *data;
    size_t len;
} RollingResult;

// Função principal traduzida
// Retorna ponteiro para array de int alocado com o mesmo tamanho da entrada
// Se len == 0, retorna NULL e define out_len a 0
int* rolling_max(const int *numbers, size_t len, size_t *out_len) {
    if (len == 0) {
        *out_len = 0;
        return NULL;
    }
    int *result = (int *)malloc(len * sizeof(int));
    if (!result) { // caso de falha de alocação
        *out_len = 0;
        return NULL;
    }
    int running_max = numbers[0];
    result[0] = running_max;
    for (size_t i = 1; i < len; ++i) {
        if (numbers[i] > running_max) {
            running_max = numbers[i];
        }
        result[i] = running_max;
    }
    *out_len = len;
    return result;
}

// Função auxiliar para comparar dois arrays de int
void assert_int_array_equal(const int *expected, const int *actual, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        assert(expected[i] == actual[i]);
    }
}

// Testes
void test_empty() {
    size_t out_len;
    int *res = rolling_max(NULL, 0, &out_len);
    assert(out_len == 0);
    assert(res == NULL);
}

void test_increasing() {
    int input[] = {1, 2, 3, 4};
    size_t out_len;
    int *res = rolling_max(input, 4, &out_len);
    assert(out_len == 4);
    int expected[] = {1, 2, 3, 4};
    assert_int_array_equal(expected, res, 4);
    free(res);
}

void test_decreasing() {
    int input[] = {4, 3, 2, 1};
    size_t out_len;
    int *res = rolling_max(input, 4, &out_len);
    assert(out_len == 4);
    int expected[] = {4, 4, 4, 4};
    assert_int_array_equal(expected, res, 4);
    free(res);
}

void test_mixed() {
    int input[] = {3, 2, 3, 100, 3};
    size_t out_len;
    int *res = rolling_max(input, 5, &out_len);
    assert(out_len == 5);
    int expected[] = {3, 3, 3, 100, 100};
    assert_int_array_equal(expected, res, 5);
    free(res);
}

int main(void) {
    test_empty();
    test_increasing();
    test_decreasing();
    test_mixed();
    return 0;
}