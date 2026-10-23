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
    const char *string;
    const char *substring;
    int result;
} TestCase;

int str_len(const char *s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}

int how_many_times(const char *string, const char *substring) {
    int len_s = str_len(string);
    int len_sub = str_len(substring);
    if (len_sub == 0) return 0;  // evitar divisão por zero e comportamento indefinido
    int times = 0;
    for (int i = 0; i <= len_s - len_sub; i++) {
        int j;
        for (j = 0; j < len_sub; j++) {
            if (string[i + j] != substring[j]) break;
        }
        if (j == len_sub) times++;
    }
    return times;
}

void check(int (*candidate)(const char *, const char *)) {
    assert(candidate("", "x") == 0);
    assert(candidate("xyxyxyx", "x") == 4);
    assert(candidate("cacacacac", "cac") == 4);
    assert(candidate("john doe", "john") == 1);
    /* Comentário: Nenhum teste adicional foi incluído pois todos os testes originais são
       determinísticos e não dependem de funções externas como random ou faker. */
}

int main(void) {
    check(how_many_times);
    return 0;
}