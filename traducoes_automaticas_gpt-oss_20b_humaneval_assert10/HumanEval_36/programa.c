#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Conversor de inteiro para string em decimal
// Limita o tamanho do buffer para suportar números até 9 dígitos (ajustável)
static void int_to_str(int num, char *buf, int *len) {
    if (num == 0) {
        buf[0] = '0';
        *len = 1;
        return;
    }
    int pos = 0;
    int temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        buf[pos++] = '0' + digit;
        temp /= 10;
    }
    // Inverte a string para obter a ordem correta
    *len = pos;
    for (int i = 0; i < pos / 2; ++i) {
        char t = buf[i];
        buf[i] = buf[pos - 1 - i];
        buf[pos - 1 - i] = t;
    }
}

// Função principal traduzida: conta quantas vezes o dígito '7' aparece
// em números menores que n que são divisíveis por 11 ou 13.
int fizz_buzz(int n) {
    int ans = 0;
    char buf[32];
    int len;
    for (int i = 0; i < n; ++i) {
        if (i % 11 == 0 || i % 13 == 0) {
            int_to_str(i, buf, &len);
            for (int j = 0; j < len; ++j) {
                if (buf[j] == '7')
                    ++ans;
            }
        }
    }
    return ans;
}

// Funções de teste correspondentes ao bloco `check` do Python
static void test_fizz_buzz(void) {
    // Testes originais
    assert(fizz_buzz(50) == 0);
    assert(fizz_buzz(78) == 2);
    assert(fizz_buzz(79) == 3);
    assert(fizz_buzz(100) == 3);
    assert(fizz_buzz(200) == 6);
    assert(fizz_buzz(4000) == 192);
    assert(fizz_buzz(10000) == 639);
    assert(fizz_buzz(100000) == 8026);
}

// Função principal que executa os testes
int main(void) {
    test_fizz_buzz();
    return 0;
}