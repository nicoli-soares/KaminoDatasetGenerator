#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Função principal traduzida
// rolling_max: recebe um array de inteiros e seu tamanho,
// preenche o array 'out' com os valores máximos acumulados.
int rolling_max(const int *numbers, int n, int *out) {
    if (n <= 0) return 0;                // lista vazia: nada a fazer

    int running_max_set = 0;
    int running_max_value = 0;

    for (int i = 0; i < n; ++i) {
        int current = numbers[i];
        if (!running_max_set) {
            running_max_set = 1;
            running_max_value = current;
        } else {
            if (current > running_max_value)
                running_max_value = current;
        }
        out[i] = running_max_value;
    }
    return 0;  // sucesso
}

// Funções auxiliares de teste
// Compara dois arrays de inteiros de tamanho 'len'
void assert_array_equal(const int *a, const int *b, int len) {
    for (int i = 0; i < len; ++i) {
        assert(a[i] == b[i]);
    }
}

// Testes traduzidos do bloco de teste original
void test_rolling_max() {
    // Teste 1: lista vazia
    int out1[1];  // tamanho não importa quando n==0
    assert(rolling_max(NULL, 0, out1) == 0);

    // Teste 2: crescente
    int nums2[] = {1, 2, 3, 4};
    int out2[4];
    assert(rolling_max(nums2, 4, out2) == 0);
    int expected2[] = {1, 2, 3, 4};
    assert_array_equal(out2, expected2, 4);

    // Teste 3: decrescente
    int nums3[] = {4, 3, 2, 1};
    int out3[4];
    assert(rolling_max(nums3, 4, out3) == 0);
    int expected3[] = {4, 4, 4, 4};
    assert_array_equal(out3, expected3, 4);

    // Teste 4: misturado com pico
    int nums4[] = {3, 2, 3, 100, 3};
    int out4[5];
    assert(rolling_max(nums4, 5, out4) == 0);
    int expected4[] = {3, 3, 3, 100, 100};
    assert_array_equal(out4, expected4, 5);
}

int main() {
    test_rolling_max();
    return 0;
}