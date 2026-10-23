#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estrutura e funções auxiliares

// Função para calcular valor absoluto de double sem usar fabs()
static double abs_double(double x) {
    return x < 0.0 ? -x : x;
}

// Função principal traduzida
// Recebe array de números, seu tamanho, e ponteiros para armazenar os dois
// números mais próximos (em ordem crescente).
void find_closest_elements(double *numbers, size_t len, double *out1, double *out2) {
    if (len < 2) {
        // Caso de erro: não há pares suficientes.
        // Retornamos valores nulos (0.0) e não falhamos.
        *out1 = 0.0;
        *out2 = 0.0;
        return;
    }

    double closest_dist = -1.0;  // Indicador de não inicializado
    double a = 0.0, b = 0.0;

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = i + 1; j < len; ++j) {
            double diff = numbers[i] - numbers[j];
            double absdiff = abs_double(diff);

            if (closest_dist < 0.0 || absdiff < closest_dist) {
                closest_dist = absdiff;
                if (numbers[i] < numbers[j]) {
                    a = numbers[i];
                    b = numbers[j];
                } else {
                    a = numbers[j];
                    b = numbers[i];
                }
            }
        }
    }

    *out1 = a;
    *out2 = b;
}

// Testes traduzidos

void test1(void) {
    double arr[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    double out1, out2;
    find_closest_elements(arr, sizeof(arr)/sizeof(double), &out1, &out2);
    assert(abs_double(out1 - 3.9) < 1e-6);
    assert(abs_double(out2 - 4.0) < 1e-6);
}

void test2(void) {
    double arr[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    double out1, out2;
    find_closest_elements(arr, sizeof(arr)/sizeof(double), &out1, &out2);
    assert(abs_double(out1 - 5.0) < 1e-6);
    assert(abs_double(out2 - 5.9) < 1e-6);
}

void test3(void) {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.2};
    double out1, out2;
    find_closest_elements(arr, sizeof(arr)/sizeof(double), &out1, &out2);
    assert(abs_double(out1 - 2.0) < 1e-6);
    assert(abs_double(out2 - 2.2) < 1e-6);
}

void test4(void) {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    double out1, out2;
    find_closest_elements(arr, sizeof(arr)/sizeof(double), &out1, &out2);
    assert(abs_double(out1 - 2.0) < 1e-6);
    assert(abs_double(out2 - 2.0) < 1e-6);
}

void test5(void) {
    double arr[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    double out1, out2;
    find_closest_elements(arr, sizeof(arr)/sizeof(double), &out1, &out2);
    assert(abs_double(out1 - 2.2) < 1e-6);
    assert(abs_double(out2 - 3.1) < 1e-6);
}

// Função principal executando os testes
int main(void) {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}