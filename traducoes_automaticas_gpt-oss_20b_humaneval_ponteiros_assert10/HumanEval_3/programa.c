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
bool below_zero(const int *operations, int n) {
    long long balance = 0;          // usar long long para reduzir risco de overflow
    for (int i = 0; i < n; ++i) {
        balance += operations[i];
        if (balance < 0) {
            return true;
        }
    }
    return false;
}

// Funções de teste
void test_below_zero(void) {
    // Teste 1: lista vazia
    assert(below_zero(NULL, 0) == false);

    // Teste 2: saldo nunca fica abaixo de zero
    int ops2[] = {1, 2, -3, 1, 2, -3};
    assert(below_zero(ops2, 6) == false);

    // Teste 3: saldo fica abaixo de zero em algum ponto
    int ops3[] = {1, 2, -4, 5, 6};
    assert(below_zero(ops3, 5) == true);

    // Teste 4: saldo nunca fica abaixo de zero em sequência alternada
    int ops4[] = {1, -1, 2, -2, 5, -5, 4, -4};
    assert(below_zero(ops4, 8) == false);

    // Teste 5: saldo fica abaixo de zero na última operação
    int ops5[] = {1, -1, 2, -2, 5, -5, 4, -5};
    assert(below_zero(ops5, 8) == true);

    // Teste 6: saldo fica abaixo de zero no início da última operação
    int ops6[] = {1, -2, 2, -2, 5, -5, 4, -4};
    assert(below_zero(ops6, 8) == true);
}

// Função principal que executa os testes
int main(void) {
    test_below_zero();
    return 0;
}