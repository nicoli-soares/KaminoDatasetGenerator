#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estruturas e typedefs necessários (nenhum caso especial, apenas função principal)
bool has_close_elements(const double *numbers, int n, double threshold) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double diff = numbers[i] - numbers[j];
                if (diff < 0) diff = -diff;
                if (diff < threshold) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Funções de teste
void test1() {
    double arr[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    assert(has_close_elements(arr, 6, 0.3) == true);
}

void test2() {
    double arr[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    assert(has_close_elements(arr, 6, 0.05) == false);
}

void test3() {
    double arr[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    assert(has_close_elements(arr, 5, 0.95) == true);
}

void test4() {
    double arr[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    assert(has_close_elements(arr, 5, 0.8) == false);
}

void test5() {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    assert(has_close_elements(arr, 6, 0.1) == true);
}

void test6() {
    double arr[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    assert(has_close_elements(arr, 5, 1.0) == true);
}

void test7() {
    double arr[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    assert(has_close_elements(arr, 5, 0.5) == false);
}

// Função principal executando os testes
int main(void) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    return 0; // Todos os asserts passaram
}