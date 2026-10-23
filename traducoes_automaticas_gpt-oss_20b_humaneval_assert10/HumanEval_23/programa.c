#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Função que retorna o tamanho de uma string
int strlen_c(const char *string) {
    int len = 0;
    while (string[len] != '\0') {
        len++;
    }
    return len;
}

// Teste: string vazia
void test_strlen_empty(void) {
    assert(strlen_c("") == 0);
}

// Teste: string com um caractere
void test_strlen_one(void) {
    assert(strlen_c("x") == 1);
}

// Teste: string com vários caracteres
void test_strlen_long(void) {
    assert(strlen_c("asdasnakj") == 9);
}

int main(void) {
    test_strlen_empty();
    test_strlen_one();
    test_strlen_long();
    return 0;
}