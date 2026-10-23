#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Função que determina se um número inteiro de 64 bits é primo
bool is_prime(long long n) {
    if (n < 2) {
        return false;
    }
    for (long long k = 2; k <= n - 2; ++k) {
        if (n % k == 0) {
            return false;
        }
    }
    return true;
}

// Função de teste que verifica os cenários fornecidos
void check(void) {
    assert(is_prime(6) == false);
    assert(is_prime(101) == true);
    assert(is_prime(11) == true);
    assert(is_prime(13441) == true);
    assert(is_prime(61) == true);
    assert(is_prime(4) == false);
    assert(is_prime(1) == false);
    assert(is_prime(5) == true);
    assert(is_prime(11) == true);
    assert(is_prime(17) == true);
    assert(is_prime(5 * 17) == false);
    assert(is_prime(11 * 7) == false);
    assert(is_prime(13441 * 19) == false);
}

// Função principal que executa os testes
int main(void) {
    check();
    return 0;
}