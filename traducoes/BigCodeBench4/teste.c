#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int numero;
    int contagem;
} ContagemPar;

void task_func(int **listas, int *tamanhos, int num_listas,
               ContagemPar *resultado, int *tamanho_resultado) {
    *tamanho_resultado = 0;

    int i, j, k;
    for ( i = 0; i < num_listas; i++) {
        for (j = 0; j < tamanhos[i]; j++) {
            int numero = listas[i][j];
            int encontrado = 0;

            for (k = 0; k < *tamanho_resultado; k++) {
                if (resultado[k].numero == numero) {
                    resultado[k].contagem++;
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                resultado[*tamanho_resultado].numero = numero;
                resultado[*tamanho_resultado].contagem = 1;
                (*tamanho_resultado)++;
            }
        }
    }
}

int buscar_contagem(ContagemPar *resultado, int tamanho, int numero) {
    int i;
    for (i = 0; i < tamanho; i++) {
        if (resultado[i].numero == numero) {
            return resultado[i].contagem;
        }
    }
    return 0; // nao encontrado
}

void test_case_1() {
    //  {'a': [1], 'b': [2], 'c': [3]}
    int lista_a[] = {1};
    int lista_b[] = {2};
    int lista_c[] = {3};
    int *listas[] = {lista_a, lista_b, lista_c};
    int tamanhos[] = {1, 1, 1};

    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(listas, tamanhos, 3, resultado, &tamanho_resultado);

    // Esperado: {1: 1, 2: 1, 3: 1}
    assert(tamanho_resultado == 3);
    assert(buscar_contagem(resultado, tamanho_resultado, 1) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 2) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 3) == 1);

    printf("test_case_1 passou!\n");
}

void test_case_3() {
    // Equivalente ao Python: {'a': [1, 1, 2], 'b': [3, 4, 4], 'c': [5, 5, 5]}
    int lista_a[] = {1, 1, 2};
    int lista_b[] = {3, 4, 4};
    int lista_c[] = {5, 5, 5};
    int *listas[] = {lista_a, lista_b, lista_c};
    int tamanhos[] = {3, 3, 3};

    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(listas, tamanhos, 3, resultado, &tamanho_resultado);

    // Esperado: {1: 2, 2: 1, 3: 1, 4: 2, 5: 3}
    assert(buscar_contagem(resultado, tamanho_resultado, 1) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, 2) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 3) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 4) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, 5) == 3);

    printf("test_case_3 passou!\n");
}

void test_case_4() {
    // Equivalente ao Python: {} (dicionario vazio)
    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(NULL, NULL, 0, resultado, &tamanho_resultado);

    // Esperado: {} (vazio)
    assert(tamanho_resultado == 0);

    printf("test_case_4 passou!\n");
}

int main() {
    test_case_1();
    test_case_3();
    test_case_4();
    printf("\nTodos os testes passaram!\n");
    return 0;
}