#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef struct {
    int valor;
} Transacao;

typedef struct {
    int saldo;
} Conta;

void inicializa_conta(Conta *conta) {
    conta->saldo = 0;
}

int below_zero_c(const Transacao transacoes[], int tamanho) {
    Conta conta;
    inicializa_conta(&conta);

    for (int i = 0; i < tamanho; i++) {
        conta.saldo += transacoes[i].valor;
        if (conta.saldo < 0) {
            return 1;
        }
    }

    return 0;
}

void testa_bellow_zero() {
    assert(below_zero_c(NULL, 0) == 0);
    assert(below_zero_c((Transacao[]){{1}, {2}, {3}}, 3) == 0);
    assert(below_zero_c((Transacao[]){{1}, {2}, {-4}, {5}}, 4) == 1);
    assert(below_zero_c((Transacao[]){{1}, {2}, {-3}, {1}, {2}, {-3}}, 6) == 0);
    assert(below_zero_c((Transacao[]){{1}, {2}, {-4}, {5}, {6}}, 5) == 1);
    assert(below_zero_c((Transacao[]){{1}, {-1}, {2}, {-2}, {5}, {-5}, {4}, {-4}}, 8) == 0);
    assert(below_zero_c((Transacao[]){{1}, {-1}, {2}, {-2}, {5}, {-5}, {4}, {-5}}, 8) == 1);
    assert(below_zero_c((Transacao[]){{1}, {-2}, {2}, {-2}, {5}, {-5}, {4}, {-4}}, 8) == 1);
}

int main() {
    testa_bellow_zero();
    return 0;
}