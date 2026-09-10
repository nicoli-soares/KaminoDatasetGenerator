#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numero;
    int contagem;
} ContagemPar;

void task_func(int **listas, int *tamanhos, int num_listas,
               ContagemPar *resultado, int *tamanho_resultado) {
    *tamanho_resultado = 0;

    int i, j, k;
    for ( i = 0; i < num_listas; i++) {
        for ( j = 0; j < tamanhos[i]; j++) {
            int numero = listas[i][j];
            int encontrado = 0;

            //equivale ao Counter
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
