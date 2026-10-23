#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    int count;
    int *array;
} IntArray;

/* Função auxiliar para contar dígitos de um inteiro positivo */
int digits_of_int(int x) {
    if (x == 0) return 1;
    int count = 0;
    while (x > 0) {
        count++;
        x /= 10;
    }
    return count;
}

/* Função principal traduzida: gera sequência de números separados por espaço */
char *string_sequence(int n) {
    if (n < 0) return NULL;  /* caso de erro: entrada negativa não suportada */

    /* Calcula comprimento necessário: dígitos + espaços + terminador nulo */
    int total_digits = 0;
    for (int i = 0; i <= n; i++) {
        total_digits += digits_of_int(i);
    }
    int total_spaces = (n > 0) ? n : 0;
    int buffer_size = total_digits + total_spaces + 1;  /* +1 para '\0' */

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) return NULL;  /* falha de alocação */

    int pos = 0;
    for (int i = 0; i <= n; i++) {
        /* Escreve o número na posição atual */
        int written = snprintf(buffer + pos, buffer_size - pos, "%d", i);
        pos += written;
        if (i < n) {  /* adiciona espaço depois de cada número, exceto o último */
            buffer[pos++] = ' ';
        }
    }
    buffer[pos] = '\0';
    return buffer;
}

/* Testes traduzidos do Python */
void test_string_sequence(void) {
    char *res;

    res = string_sequence(0);
    assert(strcmp(res, "0") == 0);
    free(res);

    res = string_sequence(3);
    assert(strcmp(res, "0 1 2 3") == 0);
    free(res);

    res = string_sequence(10);
    assert(strcmp(res, "0 1 2 3 4 5 6 7 8 9 10") == 0);
    free(res);
}

/* Função main executa todos os testes */
int main(void) {
    test_string_sequence();
    return 0;
}