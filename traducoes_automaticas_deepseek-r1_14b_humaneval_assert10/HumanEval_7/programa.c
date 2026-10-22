#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Função que filtra uma lista de strings mantendo apenas aquelas que contêm um substring específico.
 */
char** filter_by_substring_c(char* strings[], char* substring, int len) {
    if (strings == NULL) {
        return NULL;
    }
    
    int count = 0;
    int i;

    // Contar quantos elementos satisfazem a condição
    for (i = 0; i < len; i++) {
        if (strstr(strings[i], substring) != NULL) {
            count++;
        }
    }

    // Alocar memória para o resultado
    char** result = (char**)malloc(count * sizeof(char*));

    // Preencher o resultado
    int j = 0;
    for (i = 0; i < len; i++) {
        if (strstr(strings[i], substring) != NULL) {
            result[j++] = strings[i];
        }
    }

    return result;
}

/**
 * Testes para a função filter_by_substring_c
 */
void test_filter_by_substring_c() {
    // Teste 1: Lista vazia
    char** result = filter_by_substring_c(NULL, "john", 0);
    assert(result == NULL);

    // Teste 2: Substring "xxx"
    char* strings[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    char* expected[] = {"xxx", "xxxAAA", "xxx"};
    char** result2 = filter_by_substring_c(strings, "xxx", 6);
    assert(result2 != NULL);
    int i;
    for (i = 0; i < 3; i++) {
        assert(strcmp(result2[i], expected[i]) == 0);
    }
    free(result2);

    // Teste 3: Substring "xx"
    char* strings2[] = {"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"};
    char* expected2[] = {"xxx", "aaaxxy", "xxxAAA", "xxx"};
    char** result3 = filter_by_substring_c(strings2, "xx", 6);
    assert(result3 != NULL);
    for (i = 0; i < 4; i++) {
        assert(strcmp(result3[i], expected2[i]) == 0);
    }
    free(result3);

    // Teste 4: Substring "run"
    char* strings3[] = {"grunt", "trumpet", "prune", "gruesome"};
    char* expected3[] = {"grunt", "prune"};
    char** result4 = filter_by_substring_c(strings3, "run", 4);
    assert(result4 != NULL);
    for (i = 0; i < 2; i++) {
        assert(strcmp(result4[i], expected3[i]) == 0);
    }
    free(result4);
}

int main() {
    test_filter_by_substring_c();
    return 0;
}