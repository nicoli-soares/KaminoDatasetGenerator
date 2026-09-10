#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Representa um par (soma, contagem) - equivalente a uma entrada do Counter em Python
typedef struct {
    int soma;
    int contagem;
} ContagemPar;

// Adiciona uma soma ao array de contagens (ou incrementa se ja existir)
void adicionar_soma(ContagemPar *resultado, int *tamanho_resultado, int soma) {
    for (int i = 0; i < *tamanho_resultado; i++) {
        if (resultado[i].soma == soma) {
            resultado[i].contagem++;
            return;
        }
    }
    resultado[*tamanho_resultado].soma = soma;
    resultado[*tamanho_resultado].contagem = 1;
    (*tamanho_resultado)++;
}

// Funcao recursiva que gera combinacoes (equivalente ao itertools.combinations)
// elements: array original de numeros
// n: tamanho do array original
// subset_size: tamanho de cada combinacao (equivalente ao parametro subset_size do Python)
// atual: array temporario guardando a combinacao sendo construida
// pos_atual: quantos elementos ja foram escolhidos na combinacao atual
// inicio: a partir de qual indice do array original podemos escolher (evita repetir combinacoes)
// resultado / tamanho_resultado: onde acumulamos as contagens das somas
void gerar_combinacoes(int *elements, int n, int subset_size,int *atual, int pos_atual, int inicio, ContagemPar *resultado, int *tamanho_resultado) {
    if (pos_atual == subset_size) {
        int soma = 0;
        for (int i = 0; i < subset_size; i++) {
            soma += atual[i];
        }
        adicionar_soma(resultado, tamanho_resultado, soma);
        return;
    }

    // Tenta escolher cada elemento a partir de "inicio" em diante
    for (int i = inicio; i < n; i++) {
        atual[pos_atual] = elements[i];
        gerar_combinacoes(elements, n, subset_size, atual, pos_atual + 1, i + 1, resultado, tamanho_resultado);
    }
}

// equivalente ao task_func do Python
void task_func(int *elements, int n, int subset_size,ContagemPar *resultado, int *tamanho_resultado) {
    int *atual = malloc(subset_size * sizeof(int));
    *tamanho_resultado = 0;

    gerar_combinacoes(elements, n, subset_size, atual, 0, 0, resultado, tamanho_resultado);

    free(atual);
}