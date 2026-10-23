#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Estrutura para armazenar os fatores primos */
#define MAX_FACTORS 64

/* Função principal: fatoriza o número n */
void factorize(int n, int *out_factors, int *out_count) {
    int count = 0;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            if (count < MAX_FACTORS) {
                out_factors[count++] = i;
            }
            n /= i;
        } else {
            i++;
        }
    }
    if (n > 1 && count < MAX_FACTORS) {
        out_factors[count++] = n;
    }
    *out_count = count;
}

/* Funções de teste */
void test_factorize(void) {
    int factors[MAX_FACTORS];
    int count;

    /* Teste 1 */
    factorize(2, factors, &count);
    assert(count == 1);
    assert(factors[0] == 2);

    /* Teste 2 */
    factorize(4, factors, &count);
    assert(count == 2);
    assert(factors[0] == 2);
    assert(factors[1] == 2);

    /* Teste 3 */
    factorize(8, factors, &count);
    assert(count == 3);
    assert(factors[0] == 2);
    assert(factors[1] == 2);
    assert(factors[2] == 2);

    /* Teste 4 */
    factorize(57, factors, &count); /* 3 * 19 */
    assert(count == 2);
    assert(factors[0] == 3);
    assert(factors[1] == 19);

    /* Teste 5 */
    factorize(3249, factors, &count); /* 3 * 19 * 3 * 19 */
    assert(count == 4);
    assert(factors[0] == 3);
    assert(factors[1] == 3);
    assert(factors[2] == 19);
    assert(factors[3] == 19);

    /* Teste 6 */
    factorize(185193, factors, &count); /* 3 * 19 * 3 * 19 * 3 * 19 */
    assert(count == 6);
    assert(factors[0] == 3);
    assert(factors[1] == 3);
    assert(factors[2] == 3);
    assert(factors[3] == 19);
    assert(factors[4] == 19);
    assert(factors[5] == 19);

    /* Teste 7 */
    factorize(20577, factors, &count); /* 3 * 19 * 19 * 19 */
    assert(count == 4);
    assert(factors[0] == 3);
    assert(factors[1] == 19);
    assert(factors[2] == 19);
    assert(factors[3] == 19);

    /* Teste 8 */
    factorize(18, factors, &count); /* 3 * 2 * 3 */
    assert(count == 3);
    assert(factors[0] == 2);
    assert(factors[1] == 3);
    assert(factors[2] == 3);
}

/* Função principal que executa os testes */
int main(void) {
    test_factorize();
    return 0;
}