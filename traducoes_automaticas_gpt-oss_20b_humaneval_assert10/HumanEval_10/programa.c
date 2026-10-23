#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Função que verifica se uma string é palíndrome */
bool is_palindrome(const char* s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; ++i) {
        if (s[i] != s[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

/* Função principal a ser traduzida */
char* make_palindrome(const char* string) {
    if (!string) return NULL;           /* Segurança: caso de ponteiro nulo */
    size_t len = strlen(string);
    if (len == 0) {                     /* Caso base: string vazia */
        char *empty = malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    size_t beginning_of_suffix = 0;
    /* Procura o maior sufixo que seja palíndrome */
    while (!is_palindrome(string + beginning_of_suffix)) {
        ++beginning_of_suffix;
    }

    size_t result_len = len + beginning_of_suffix;
    char *result = malloc(result_len + 1);   /* +1 para o terminador NUL */
    if (!result) return NULL;

    /* Copia a string original */
    strcpy(result, string);

    /* Adiciona o reverso do prefixo que precede o sufixo palíndrome */
    for (size_t i = 0; i < beginning_of_suffix; ++i) {
        result[len + i] = string[beginning_of_suffix - 1 - i];
    }
    result[result_len] = '\0';
    return result;
}

/* Funções de teste que verificam a correção da implementação */
void test_make_palindrome(void) {
    char *res;

    res = make_palindrome("");
    assert(strcmp(res, "") == 0);
    free(res);

    res = make_palindrome("x");
    assert(strcmp(res, "x") == 0);
    free(res);

    res = make_palindrome("xyz");
    assert(strcmp(res, "xyzyx") == 0);
    free(res);

    res = make_palindrome("xyx");
    assert(strcmp(res, "xyx") == 0);
    free(res);

    res = make_palindrome("jerry");
    assert(strcmp(res, "jerryrrej") == 0);
    free(res);
}

/* Função principal que executa todos os testes */
int main(void) {
    test_make_palindrome();
    return 0;
}