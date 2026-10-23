#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Função principal traduzida */
double mean_absolute_deviation(const double *numbers, int len) {
    if (len <= 0) {
        /* Caso não previsto nos testes: retorno 0 para evitar divisão por zero */
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < len; ++i) {
        sum += numbers[i];
    }
    double mean = sum / len;
    double sum_abs = 0.0;
    for (int i = 0; i < len; ++i) {
        double diff = numbers[i] - mean;
        if (diff < 0) diff = -diff;          /* equivalente a abs() */
        sum_abs += diff;
    }
    return sum_abs / len;
}

/* Funções de teste correspondentes aos testes Python */
void test_mean_absolute_deviation_1(void) {
    double arr[] = {1.0, 2.0, 3.0};
    double expected = 2.0 / 3.0;
    double result = mean_absolute_deviation(arr, 3);
    assert(fabs(result - expected) < 1e-6);
}

void test_mean_absolute_deviation_2(void) {
    double arr[] = {1.0, 2.0, 3.0, 4.0};
    double expected = 1.0;
    double result = mean_absolute_deviation(arr, 4);
    assert(fabs(result - expected) < 1e-6);
}

void test_mean_absolute_deviation_3(void) {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double expected = 6.0 / 5.0;
    double result = mean_absolute_deviation(arr, 5);
    assert(fabs(result - expected) < 1e-6);
}

/* Função main que executa todos os testes */
int main(void) {
    test_mean_absolute_deviation_1();
    test_mean_absolute_deviation_2();
    test_mean_absolute_deviation_3();
    return 0;
}