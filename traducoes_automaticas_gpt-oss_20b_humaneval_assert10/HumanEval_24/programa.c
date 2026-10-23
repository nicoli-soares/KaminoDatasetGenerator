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
int largest_divisor(int n) {
    // Busca do maior divisor menor que n
    for (int i = n - 1; i > 0; --i) {
        if (n % i == 0) {
            return i;
        }
    }
    // Caso n <= 1, não há divisor válido; retornar 0 como padrão
    return 0;
}

// Função de teste que recebe ponteiro para a função a ser testada
void check(int (*candidate)(int)) {
    // Testes baseados nos exemplos do docstring original
    assert(candidate(3) == 1);
    assert(candidate(7) == 1);
    assert(candidate(10) == 5);
    assert(candidate(100) == 50);
    assert(candidate(49) == 7);
    // Comentário: não há testes que dependem de random, Faker ou apenas de isinstance, então nenhum teste foi omitido.
}

// Função principal que executa os testes
int main(void) {
    check(largest_divisor);
    return 0;
}