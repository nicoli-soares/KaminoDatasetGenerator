#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Tradução de triples_sum_to_zero e seus testes em C */

int triples_sum_to_zero(const int *l, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (l[i] + l[j] + l[k] == 0) {
                    return 1; /* verdadeiro */
                }
            }
        }
    }
    return 0; /* falso */
}

/* Testes unitários */
void run_tests(void) {
    /* Teste 1 */
    int a1[] = {1, 3, 5, 0};
    assert(triples_sum_to_zero(a1, 4) == 0);

    /* Teste 2 */
    int a2[] = {1, 3, 5, -1};
    assert(triples_sum_to_zero(a2, 4) == 0);

    /* Teste 3 */
    int a3[] = {1, 3, -2, 1};
    assert(triples_sum_to_zero(a3, 4) == 1);

    /* Teste 4 */
    int a4[] = {1, 2, 3, 7};
    assert(triples_sum_to_zero(a4, 4) == 0);

    /* Teste 5 */
    int a5[] = {1, 2, 5, 7};
    assert(triples_sum_to_zero(a5, 4) == 0);

    /* Teste 6 */
    int a6[] = {2, 4, -5, 3, 9, 7};
    assert(triples_sum_to_zero(a6, 6) == 1);

    /* Teste 7 */
    int a7[] = {1};
    assert(triples_sum_to_zero(a7, 1) == 0);

    /* Teste 8 */
    int a8[] = {1, 3, 5, -100};
    assert(triples_sum_to_zero(a8, 4) == 0);

    /* Teste 9 */
    int a9[] = {100, 3, 5, -100};
    assert(triples_sum_to_zero(a9, 4) == 0);
}

/* Função principal que executa os testes */
int main(void) {
    run_tests();
    return 0;
}