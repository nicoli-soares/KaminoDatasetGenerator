#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef double (*func_ptr)(double);

/* Função principal traduzida: retorna a parte fracionária de um número positivo */
double truncate_number(double number) {
    /* Para números positivos, o inteiro menor ou igual é dado pelo cast para long long */
    long long inteiro = (long long)number;
    return number - (double)inteiro;
}

/* Função de teste que recebe um ponteiro para a função a ser testada */
void check(func_ptr candidate) {
    /* Teste 1: 3.5 → 0.5 */
    assert(fabs(candidate(3.5) - 0.5) < 1e-6);
    /* Teste 2: 1.33 → 0.33 */
    assert(fabs(candidate(1.33) - 0.33) < 1e-6);
    /* Teste 3: 123.456 → 0.456 */
    assert(fabs(candidate(123.456) - 0.456) < 1e-6);
}

int main(void) {
    /* Executa os testes passando a função traduzida */
    check(truncate_number);
    return 0;
}