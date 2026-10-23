#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Função principal traduzida: retorna o maior elemento de um vetor de inteiros */
int max_element(const int *l, int n) {
    int m = l[0];
    for (int i = 0; i < n; i++) {
        if (l[i] > m) {
            m = l[i];
        }
    }
    return m;
}

/* Função de teste que reproduz os casos de uso do docstring original */
void test_max_element(void) {
    int arr1[] = {1, 2, 3};
    assert(max_element(arr1, 3) == 3);

    int arr2[] = {5, 3, -5, 2, -3, 3, 9, 0, 124, 1, -10};
    assert(max_element(arr2, 11) == 124);
}

/* Função main que executa os testes */
int main(void) {
    test_max_element();
    return 0;
}