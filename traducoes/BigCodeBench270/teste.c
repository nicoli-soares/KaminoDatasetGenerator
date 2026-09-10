#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define MAX_PALAVRA 256
#define MAX_PALAVRAS_DISTINTAS 512

// equivalente a uma entrada do Counter
typedef struct {
    char palavra[MAX_PALAVRA];
    int contagem;
} ContagemPalavra;

// Equivalente ao que \w significa em regex: letras, digitos e underscore
int eh_caractere_de_palavra(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

void adicionar_palavra(ContagemPalavra *resultado, int *tamanho_resultado, const char *palavra) {
    int i;
    for ( i = 0; i < *tamanho_resultado; i++) {
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

// equivalente ao task_func do Python
void task_func(const char *sentence, ContagemPalavra *resultado, int *tamanho_resultado) {
    *tamanho_resultado = 0;

    char palavra_atual[MAX_PALAVRA];
    int pos = 0;

    int i;
    for ( i = 0; sentence[i] != '\0'; i++) {
        if (eh_caractere_de_palavra(sentence[i])) {
            if (pos < MAX_PALAVRA - 1) {
                palavra_atual[pos++] = sentence[i];
            }
        } else {
            // Encontrou um separador (espaco, pontuacao, etc.) - fecha a palavra atual
            if (pos > 0) {
                palavra_atual[pos] = '\0';
                adicionar_palavra(resultado, tamanho_resultado, palavra_atual);
                pos = 0;
            }
        }
    }

    // Nao esquecer da ultima palavra, caso a frase nao termine com separador
    if (pos > 0) {
        palavra_atual[pos] = '\0';
        adicionar_palavra(resultado, tamanho_resultado, palavra_atual);
    }
}

int buscar_contagem(ContagemPalavra *resultado, int tamanho, const char *palavra) {
    int i;
    for ( i = 0; i < tamanho; i++) {
        if (strcmp(resultado[i].palavra, palavra) == 0) {
            return resultado[i].contagem;
        }
    }
    return 0;
}

void test_empty_string() {
    // task_func("") -> {}
    ContagemPalavra resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho_resultado;

    task_func("", resultado, &tamanho_resultado);

    assert(tamanho_resultado == 0);
    printf("test_empty_string passou!\n");
}

void test_case_sensitivity() {
    // 'Apple apple' -> {"Apple": 1, "apple": 1}
    ContagemPalavra resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho_resultado;

    task_func("Apple apple", resultado, &tamanho_resultado);

    assert(tamanho_resultado == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, "Apple") == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, "apple") == 1);
    printf("test_case_sensitivity passou!\n");
}

void test_punctuation_inclusion() {
    // 'apple, apple; banana!' -> {"apple": 2, "banana": 1}
    ContagemPalavra resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho_resultado;

    task_func("apple, apple; banana!", resultado, &tamanho_resultado);

    assert(tamanho_resultado == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, "apple") == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, "banana") == 1);
    printf("test_punctuation_inclusion passou!\n");
}

void test_numeric_and_special_characters() {
    // '123 $%^& 123' -> {'123': 2}
    ContagemPalavra resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho_resultado;

    task_func("123 $%^& 123", resultado, &tamanho_resultado);

    assert(tamanho_resultado == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, "123") == 2);
    printf("test_numeric_and_special_characters passou!\n");
}

int main() {
    test_empty_string();
    test_case_sensitivity();
    test_punctuation_inclusion();
    test_numeric_and_special_characters();
    printf("\nTodos os testes passaram!\n");
    return 0;
}