#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estruturas e tipos necessários (nenhum struct é requerido para esta função)


/* Função auxiliar para calcular o valor absoluto de um double */
static double abs_double(double x) {
    return x < 0.0 ? -x : x;
}

/*
 * Função rescale_to_unit
 *   numbers  - ponteiro para o array de entrada de doubles
 *   n        - tamanho do array de entrada (deve ser >= 2)
 *   output   - ponteiro para o array onde o resultado será armazenado
 *
 * Retorno:
 *   0   se a operação for bem-sucedida
 *  -1   se n < 2 (entrada inválida)
 */
int rescale_to_unit(const double *numbers, int n, double *output) {
    if (n < 2) {
        return -1; /* erro: lista deve conter pelo menos dois elementos */
    }

    double min_number = numbers[0];
    double max_number = numbers[0];

    /* Encontrar mínimo e máximo */
    for (int i = 1; i < n; i++) {
        if (numbers[i] < min_number) {
            min_number = numbers[i];
        }
        if (numbers[i] > max_number) {
            max_number = numbers[i];
        }
    }

    double denom = max_number - min_number;
    /* Se todos os números forem iguais, denom será 0; nesse caso, todos os
       valores de saída serão 0.0 (código de negócio não especifica outro
       comportamento, mas evita divisão por zero). */
    for (int i = 0; i < n; i++) {
        if (abs_double(denom) < 1e-12) {
            output[i] = 0.0;
        } else {
            output[i] = (numbers[i] - min_number) / denom;
        }
    }

    return 0;
}

/* Função de teste: verifica vários cenários de entrada e saída */
void check(void) {
    /* Teste 1 */
    double input1[] = {2.0, 49.9};
    int n1 = sizeof(input1) / sizeof(input1[0]);
    double expected1[] = {0.0, 1.0};
    double *out1 = (double *)malloc(n1 * sizeof(double));
    assert(rescale_to_unit(input1, n1, out1) == 0);
    for (int i = 0; i < n1; i++) {
        assert(abs_double(out1[i] - expected1[i]) < 1e-6);
    }
    free(out1);

    /* Teste 2 */
    double input2[] = {100.0, 49.9};
    int n2 = sizeof(input2) / sizeof(input2[0]);
    double expected2[] = {1.0, 0.0};
    double *out2 = (double *)malloc(n2 * sizeof(double));
    assert(rescale_to_unit(input2, n2, out2) == 0);
    for (int i = 0; i < n2; i++) {
        assert(abs_double(out2[i] - expected2[i]) < 1e-6);
    }
    free(out2);

    /* Teste 3 */
    double input3[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int n3 = sizeof(input3) / sizeof(input3[0]);
    double expected3[] = {0.0, 0.25, 0.5, 0.75, 1.0};
    double *out3 = (double *)malloc(n3 * sizeof(double));
    assert(rescale_to_unit(input3, n3, out3) == 0);
    for (int i = 0; i < n3; i++) {
        assert(abs_double(out3[i] - expected3[i]) < 1e-6);
    }
    free(out3);

    /* Teste 4 */
    double input4[] = {2.0, 1.0, 5.0, 3.0, 4.0};
    int n4 = sizeof(input4) / sizeof(input4[0]);
    double expected4[] = {0.25, 0.0, 1.0, 0.5, 0.75};
    double *out4 = (double *)malloc(n4 * sizeof(double));
    assert(rescale_to_unit(input4, n4, out4) == 0);
    for (int i = 0; i < n4; i++) {
        assert(abs_double(out4[i] - expected4[i]) < 1e-6);
    }
    free(out4);

    /* Teste 5 */
    double input5[] = {12.0, 11.0, 15.0, 13.0, 14.0};
    int n5 = sizeof(input5) / sizeof(input5[0]);
    double expected5[] = {0.25, 0.0, 1.0, 0.5, 0.75};
    double *out5 = (double *)malloc(n5 * sizeof(double));
    assert(rescale_to_unit(input5, n5, out5) == 0);
    for (int i = 0; i < n5; i++) {
        assert(abs_double(out5[i] - expected5[i]) < 1e-6);
    }
    free(out5);
}

int main(void) {
    check();
    return 0;
}