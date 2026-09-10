#include <math.h>
#define MAX_COMBINACAO 64

static void gerar_combinacoes_r(int *numbers, int n, int r,
                                 int *atual, int pos_atual, int inicio,
                                 double *soma, int *erro) {
    if (*erro) return; // ja encontramos erro antes, nao continua

    if (pos_atual == r) {
        long long produto = 1;
        for (int i = 0; i < r; i++) {
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

    for (int i = inicio; i < n; i++) {
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

    for (int r = 1; r <= n; r++) {
        gerar_combinacoes_r(numbers, n, r, atual, 0, 0, &soma, &erro);
        if (erro) {
            return -1;
        }
    }

    *resultado = soma;
    return 0;
}