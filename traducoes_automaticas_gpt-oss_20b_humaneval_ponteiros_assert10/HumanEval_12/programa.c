#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Função auxiliar para obter o tamanho de uma string */
int my_strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

/* Função principal: retorna o índice da string mais longa ou -1 se vazio.
   O resultado (a string mais longa) é copiado para 'out'.
   - strings: array de ponteiros para strings
   - n: número de strings no array
   - out: buffer onde a string mais longa será copiada
   - out_size: tamanho do buffer 'out' (inclui espaço para terminador '\0')
   Retorna 0 em sucesso, -1 se a lista estiver vazia, -2 se o buffer for pequeno.
*/
int longest(const char *strings[], int n, char *out, int out_size) {
    if (n <= 0) {
        return -1; /* lista vazia */
    }

    /* Encontrar comprimento máximo */
    int maxlen = 0;
    for (int i = 0; i < n; i++) {
        int len = my_strlen(strings[i]);
        if (len > maxlen) {
            maxlen = len;
        }
    }

    /* Encontrar e copiar a primeira string com comprimento máximo */
    for (int i = 0; i < n; i++) {
        if (my_strlen(strings[i]) == maxlen) {
            int len = maxlen; /* já sabemos que é igual a maxlen */
            if (len + 1 > out_size) {
                return -2; /* buffer insuficiente */
            }
            for (int j = 0; j < len; j++) {
                out[j] = strings[i][j];
            }
            out[len] = '\0';
            return 0; /* sucesso */
        }
    }

    /* Caso teoricamente impossível de chegar aqui */
    return -3;
}

/* Funções de teste */
void test_longest(void) {
    char out[256];
    int res;

    /* Teste 1: lista vazia */
    res = longest(NULL, 0, out, sizeof(out));
    assert(res == -1);

    /* Teste 2: três strings de mesmo tamanho */
    const char *s1[] = {"x", "y", "z"};
    res = longest(s1, 3, out, sizeof(out));
    assert(res == 0);
    assert(out[0] == 'x' && out[1] == '\0');

    /* Teste 3: strings de diferentes comprimentos */
    const char *s2[] = {"x", "yyy", "zzzz", "www", "kkkk", "abc"};
    res = longest(s2, 6, out, sizeof(out));
    assert(res == 0);
    assert(out[0] == 'z' && out[1] == 'z' && out[2] == 'z' && out[3] == 'z' && out[4] == '\0');
}

/* Função principal que executa os testes */
int main(void) {
    test_longest();
    return 0;
}