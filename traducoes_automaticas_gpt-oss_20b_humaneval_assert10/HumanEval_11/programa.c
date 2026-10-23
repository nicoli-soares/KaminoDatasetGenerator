#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Estrutura para armazenar pares de caracteres (não necessária aqui) */
typedef struct {
    char a;
    char b;
} ParChars;

/* Função auxiliar para comparar dois caracteres como se fossem bits binários */
static char xor_char(char x, char y) {
    return (x == y) ? '0' : '1';
}

/* Função que retorna o comprimento de uma string (sem usar string.h) */
static size_t my_strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

/* Função que compara duas strings (sem usar string.h) */
static int my_strcmp(const char *s1, const char *s2) {
    size_t i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return (s1[i] < s2[i]) ? -1 : 1;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 0;
    }
    return (s1[i] == '\0') ? -1 : 1;
}

/* Função principal: realiza XOR bit a bit em duas strings binárias
   out: buffer onde será armazenada a string resultante
   out_len: tamanho do buffer out (deve ser >= tamanho de a + 1)
   Retorna 0 em caso de sucesso, -1 se os comprimentos forem diferentes,
   ou -2 se o buffer for insuficiente. */
int string_xor(const char *a, const char *b, char *out, size_t out_len) {
    size_t len_a = my_strlen(a);
    size_t len_b = my_strlen(b);
    if (len_a != len_b) {
        return -1; /* comprimentos diferentes */
    }
    if (out_len <= len_a) {
        return -2; /* buffer insuficiente */
    }
    for (size_t i = 0; i < len_a; i++) {
        out[i] = xor_char(a[i], b[i]);
    }
    out[len_a] = '\0';
    return 0;
}

/* Teste 1 */
void test1() {
    char out[10];
    int r = string_xor("111000", "101010", out, sizeof(out));
    assert(r == 0);
    assert(my_strcmp(out, "010010") == 0);
}

/* Teste 2 */
void test2() {
    char out[2];
    int r = string_xor("1", "1", out, sizeof(out));
    assert(r == 0);
    assert(my_strcmp(out, "0") == 0);
}

/* Teste 3 */
void test3() {
    char out[5];
    int r = string_xor("0101", "0000", out, sizeof(out));
    assert(r == 0);
    assert(my_strcmp(out, "0101") == 0);
}

/* Função principal que executa os testes */
int main(void) {
    test1();
    test2();
    test3();
    return 0;
}