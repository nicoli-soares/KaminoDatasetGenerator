#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int soma;
    int contagem;
} ContagemPar;

void adicionar_soma(ContagemPar *resultado, int *tamanho_resultado, int soma) {
    int i;
    for (i = 0; i < *tamanho_resultado; i++) {
        if (resultado[i].soma == soma) {
            resultado[i].contagem++;
            return;
        }
    }
    resultado[*tamanho_resultado].soma = soma;
    resultado[*tamanho_resultado].contagem = 1;
    (*tamanho_resultado)++;
}

void gerar_combinacoes(int *elements, int n, int subset_size, int *atual, int pos_atual, int inicio, ContagemPar *resultado, int *tamanho_resultado) {
    int i;
    if (pos_atual == subset_size) {
        int soma = 0;
        for (i = 0; i < subset_size; i++) {
            soma += atual[i];
        }
        adicionar_soma(resultado, tamanho_resultado, soma);
        return;
    }

    for (i = inicio; i < n; i++) {
        atual[pos_atual] = elements[i];
        gerar_combinacoes(elements, n, subset_size, atual, pos_atual + 1, i + 1, resultado, tamanho_resultado);
    }
}

void task_func(int *elements, int n, int subset_size,
               ContagemPar *resultado, int *tamanho_resultado) {
    int *atual = (subset_size > 0) ? malloc(subset_size * sizeof(int)) : NULL;
    *tamanho_resultado = 0;

    gerar_combinacoes(elements, n, subset_size, atual, 0, 0, resultado, tamanho_resultado);

    free(atual);
}

int buscar_contagem(ContagemPar *resultado, int tamanho, int soma) {
    int i;
    for (i = 0; i < tamanho; i++) {
        if (resultado[i].soma == soma) {
            return resultado[i].contagem;
        }
    }
    return 0;
}

void test_case_1() {
    // elements = (1, 2, 3, 4, 5), subset_size = 2
    // Esperado: Counter({3:1, 4:1, 5:2, 6:2, 7:2, 8:1, 9:1})
    int elements[] = {1, 2, 3, 4, 5};
    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(elements, 5, 2, resultado, &tamanho_resultado);

    assert(buscar_contagem(resultado, tamanho_resultado, 3) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 4) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 5) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, 6) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, 7) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, 8) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 9) == 1);
    assert(tamanho_resultado == 7); // 7 somas distintas

    printf("test_case_1 passou!\n");
}

void test_case_2() {
    // elements = (-3, -2, 0, 2, 3, 5), subset_size = 3
    // Esperado: Counter({0:3, 5:3, 2:2, 3:2, -5:1, -3:1, -2:1, -1:1, 4:1, 1:1, 6:1, 7:1, 8:1, 10:1})
    int elements[] = {-3, -2, 0, 2, 3, 5};
    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(elements, 6, 3, resultado, &tamanho_resultado);

    assert(buscar_contagem(resultado, tamanho_resultado, 0) == 3);
    assert(buscar_contagem(resultado, tamanho_resultado, 5) == 3);
    assert(buscar_contagem(resultado, tamanho_resultado, 2) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, 3) == 2);
    assert(buscar_contagem(resultado, tamanho_resultado, -5) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, -3) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, -2) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, -1) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 4) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 1) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 6) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 7) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 8) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 10) == 1);
    assert(tamanho_resultado == 14); // 14 somas distintas

    printf("test_case_2 passou!\n");
}

void test_case_3() {
    // elements = (1, 2, 3, 4, 5), subset_size = 1
    // Esperado: Counter({1:1, 2:1, 3:1, 4:1, 5:1})
    int elements[] = {1, 2, 3, 4, 5};
    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(elements, 5, 1, resultado, &tamanho_resultado);

    assert(tamanho_resultado == 5);
    assert(buscar_contagem(resultado, tamanho_resultado, 1) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 2) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 3) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 4) == 1);
    assert(buscar_contagem(resultado, tamanho_resultado, 5) == 1);

    printf("test_case_3 passou!\n");
}

void test_case_4() {
    // elements = (), subset_size = 2
    // Esperado: Counter() -> vazio
    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(NULL, 0, 2, resultado, &tamanho_resultado);

    assert(tamanho_resultado == 0);

    printf("test_case_4 passou!\n");
}

void test_case_5() {
    // elements = (1, 2, 3), subset_size = 5 (maior que a lista)
    // Esperado: Counter() -> vazio, pois nao existe combinacao possivel
    int elements[] = {1, 2, 3};
    ContagemPar resultado[100];
    int tamanho_resultado;

    task_func(elements, 3, 5, resultado, &tamanho_resultado);

    assert(tamanho_resultado == 0);

    printf("test_case_5 passou!\n");
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    printf("\nTodos os testes passaram!\n");
    return 0;
}