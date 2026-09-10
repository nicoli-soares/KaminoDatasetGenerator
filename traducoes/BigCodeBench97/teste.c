#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_COMBINACAO 64

static void gerar_combinacoes_r(int *numbers, int n, int r,
                                 int *atual, int pos_atual, int inicio,
                                 double *soma, int *erro) {
    if (*erro) return; // ja encontramos erro antes, nao continua

    if (pos_atual == r) {
        long long produto = 1;
        int i;
        for (i = 0; i < r; i++) {
            produto *= atual[i];
        }
        if (produto <= 0) {
            // equivalente ao ValueError do math.log em Python
            *erro = 1;
            return;
        }
        *soma += log((double)produto);
        return;
    }
    int i;
    for ( i = inicio; i < n; i++) {
        atual[pos_atual] = numbers[i];
        gerar_combinacoes_r(numbers, n, r, atual, pos_atual + 1, i + 1, soma, erro);
        if (*erro) return;
    }
}

// Funcao principal - equivalente ao task_func do Python
int task_func(int *numbers, int n, double *resultado) {
    double soma = 0.0;
    int erro = 0;
    int atual[MAX_COMBINACAO];

    int r;
    for ( r = 1; r <= n; r++) {
        gerar_combinacoes_r(numbers, n, r, atual, 0, 0, &soma, &erro);
        if (erro) {
            return -1;
        }
    }

    *resultado = soma;
    return 0;
}

/* ============================================================
   TESTES (traduzidos do campo "test" real do BigCodeBench/97)
   Nota: test_return_type foi OMITIDO - em C o tipo de retorno
   ja e fixo (double), entao esse teste nao se aplica.
   ============================================================ */

void test_specific_case() {
    // numbers = [2, 3]
    // esperado = log(2) + log(3) + log(2*3)
    int numbers[] = {2, 3};
    double resultado;
    int status = task_func(numbers, 2, &resultado);

    double esperado = log(2) + log(3) + log(2 * 3);

    assert(status == 0);
    assert(fabs(resultado - esperado) < 1e-9);
    printf("test_specific_case passou! resultado: %f\n", resultado);
}

void test_empty_list() {
    // numbers = [] -> esperado 0
    double resultado;
    int status = task_func(NULL, 0, &resultado);

    assert(status == 0);
    assert(resultado == 0);
    printf("test_empty_list passou! resultado: %f\n", resultado);
}

void test_large_list() {
    // numbers = [1, 2, 3, 4, 5] -> resultado deve ser >= 0
    int numbers[] = {1, 2, 3, 4, 5};
    double resultado;
    int status = task_func(numbers, 5, &resultado);

    assert(status == 0);
    assert(resultado >= 0);
    printf("test_large_list passou! resultado: %f\n", resultado);
}

void test_single_number_list() {
    // numbers = [5] -> esperado log(5)
    int numbers[] = {5};
    double resultado;
    int status = task_func(numbers, 1, &resultado);

    assert(status == 0);
    assert(fabs(resultado - log(5)) < 1e-9);
    printf("test_single_number_list passou! resultado: %f\n", resultado);
}

void test_negative_numbers() {
    // numbers = [-1, -2, -3] -> deve sinalizar erro (equivalente ao ValueError)
    int numbers[] = {-1, -2, -3};
    double resultado;
    int status = task_func(numbers, 3, &resultado);

    assert(status == -1);
    printf("test_negative_numbers passou! (erro detectado corretamente)\n");
}

int main() {
    test_specific_case();
    test_empty_list();
    test_large_list();
    test_single_number_list();
    test_negative_numbers();
    printf("\nTodos os testes passaram!\n");
    return 0;
}