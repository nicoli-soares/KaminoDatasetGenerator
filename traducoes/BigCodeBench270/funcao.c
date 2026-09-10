#define MAX_PALAVRA 256
#define MAX_PALAVRAS_DISTINTAS 512
#include <string.h>
#include <ctype.h>

// equivalente a uma entrada do Counter
typedef struct {
    char palavra[MAX_PALAVRA];
    int contagem;
} ContagemPalavra;

// Equivalente ao que \w significa em regex: letras, digitos e underscore
int eh_caractere_de_palavra(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

// Adiciona uma palavra ao array de contagens (ou incrementa se ja existir)
// A comparacao e sensivel a maiusculas/minusculas (case-sensitive),
// igual ao comportamento original em Python
void adicionar_palavra(ContagemPalavra *resultado, int *tamanho_resultado, const char *palavra) {
    for (int i = 0; i < *tamanho_resultado; i++) {
        if (strcmp(resultado[i].palavra, palavra) == 0) {
            resultado[i].contagem++;
            return;
        }
    }
    strncpy(resultado[*tamanho_resultado].palavra, palavra, MAX_PALAVRA - 1);
    resultado[*tamanho_resultado].palavra[MAX_PALAVRA - 1] = '\0';
    resultado[*tamanho_resultado].contagem = 1;
    (*tamanho_resultado)++;
}

// Funcao principal - equivalente ao task_func do Python
void task_func(const char *sentence, ContagemPalavra *resultado, int *tamanho_resultado) {
    *tamanho_resultado = 0;

    char palavra_atual[MAX_PALAVRA];
    int pos = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (eh_caractere_de_palavra(sentence[i])) {
            if (pos < MAX_PALAVRA - 1) {
                palavra_atual[pos++] = sentence[i];
            }
        } else {
            if (pos > 0) {
                palavra_atual[pos] = '\0';
                adicionar_palavra(resultado, tamanho_resultado, palavra_atual);
                pos = 0;
            }
        }
    }

    if (pos > 0) {
        palavra_atual[pos] = '\0';
        adicionar_palavra(resultado, tamanho_resultado, palavra_atual);
    }
}