#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Função que inverte a capitalização de cada caractere em uma string.
// Retorna um novo buffer alocado dinamicamente contendo o resultado.
// Em caso de falha na alocação, retorna NULL.
char* flip_case(const char *input) {
    size_t len = strlen(input);
    char *output = (char*)malloc(len + 1);
    if (!output) return NULL;  // falha de memória

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = input[i];
        if (islower(c))
            output[i] = toupper(c);
        else if (isupper(c))
            output[i] = tolower(c);
        else
            output[i] = c;  // caracteres que não são letras permanecem inalterados
    }
    output[len] = '\0';
    return output;
}

// Testes unitários --------------------------------------------------------

void test_empty() {
    char *r = flip_case("");
    assert(r != NULL);
    assert(strcmp(r, "") == 0);
    free(r);
}

void test_hello() {
    char *r = flip_case("Hello!");
    assert(r != NULL);
    assert(strcmp(r, "hELLO!") == 0);
    free(r);
}

void test_long() {
    char *r = flip_case("These violent delights have violent ends");
    assert(r != NULL);
    assert(strcmp(r, "tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS") == 0);
    free(r);
}

// Driver -------------------------------------------------------------
int main(void) {
    test_empty();
    test_hello();
    test_long();
    return 0;
}