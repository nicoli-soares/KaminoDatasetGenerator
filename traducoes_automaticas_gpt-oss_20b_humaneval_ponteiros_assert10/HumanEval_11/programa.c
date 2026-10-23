#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Função auxiliar para calcular XOR entre dois caracteres '0' e '1'
static char xor_char(char i, char j) {
    return (i == j) ? '0' : '1';
}

// Função principal: retorna uma nova string contendo o XOR bit a bit
// dos dois strings de entrada. A string resultante é alocada com malloc
// e deve ser liberada pelo chamador.
char* string_xor(const char* a, const char* b) {
    // Determina o tamanho mínimo das duas strings
    int len_a = 0;
    while (a[len_a] != '\0') len_a++;
    int len_b = 0;
    while (b[len_b] != '\0') len_b++;
    int len = (len_a < len_b) ? len_a : len_b;

    // Aloca memória para o resultado + terminador nulo
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) return NULL; // em caso de falha na alocação

    // Calcula o XOR bit a bit
    for (int i = 0; i < len; i++) {
        result[i] = xor_char(a[i], b[i]);
    }
    result[len] = '\0'; // termina a string
    return result;
}

// Testes unitários
void test1(void) {
    char* res = string_xor("111000", "101010");
    assert(res != NULL);
    assert(strcmp(res, "010010") == 0);
    free(res);
}

void test2(void) {
    char* res = string_xor("1", "1");
    assert(res != NULL);
    assert(strcmp(res, "0") == 0);
    free(res);
}

void test3(void) {
    char* res = string_xor("0101", "0000");
    assert(res != NULL);
    assert(strcmp(res, "0101") == 0);
    free(res);
}

// Função principal que executa todos os testes
int main(void) {
    test1();
    test2();
    test3();
    return 0;
}