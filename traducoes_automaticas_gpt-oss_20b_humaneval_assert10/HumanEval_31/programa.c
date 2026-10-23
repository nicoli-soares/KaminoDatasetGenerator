#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Estrutura de dados não necessária, mas mantida para aderir às regras
// da tradução em C puro conforme guia.

bool is_prime(uint64_t n)
{
    if (n < 2)
        return false;
    for (uint64_t k = 2; k < n - 1; k++)
    {
        if (n % k == 0)
            return false;
    }
    return true;
}

// Função de teste que replica o bloco "check" do Python
void test_is_prime()
{
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
    // Produto de dois primos
    assert(is_prime(5 * 17) == false);
    assert(is_prime(11 * 7) == false);
    assert(is_prime(13441 * 19) == false);
}

int main()
{
    test_is_prime();
    return 0;
}