#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PRODUTOS 100
#define MAX_NOME_PRODUTO 128
#define MAX_LINHA 256

typedef struct {
    char produto[MAX_NOME_PRODUTO];
    long quantidade_total;
} VendaProduto;

// Remove quebra de linha (\n ou \r\n) do final de uma string, in-place
static void remover_quebra_linha(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

// Retorna 0 em sucesso (nome do produto mais vendido em 'top_selling_product')
// Retorna -1 se o arquivo nao existir (equivalente ao FileNotFoundError)
// Retorna -2 se nao houver dados de vendas (equivalente ao ValueError do max() em lista vazia)
// Retorna -3 se a quantidade nao for um numero valido (equivalente ao ValueError do int())
int task_func(const char *csv_file_path, char *top_selling_product, size_t tamanho_saida) {
    FILE *f = fopen(csv_file_path, "r");
    if (f == NULL) {
        return -1;
    }

    char linha[MAX_LINHA];

    if (fgets(linha, sizeof(linha), f) == NULL) {
        fclose(f);
        return -2;
    }

    VendaProduto vendas[MAX_PRODUTOS];
    int num_produtos = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        remover_quebra_linha(linha);
        if (strlen(linha) == 0) continue;

        char *virgula = strchr(linha, ',');
        if (virgula == NULL) {
            fclose(f);
            return -3;
        }

        *virgula = '\0';
        const char *produto = linha;
        const char *quantidade_str = virgula + 1;

        char *endptr;
        long quantidade = strtol(quantidade_str, &endptr, 10);
        if (endptr == quantidade_str || *endptr != '\0') {
            fclose(f);
            return -3;
        }

        int encontrado = 0, i;
        for (i = 0; i < num_produtos; i++) {
            if (strcmp(vendas[i].produto, produto) == 0) {
                vendas[i].quantidade_total += quantidade;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado && num_produtos < MAX_PRODUTOS) {
            strncpy(vendas[num_produtos].produto, produto, MAX_NOME_PRODUTO - 1);
            vendas[num_produtos].produto[MAX_NOME_PRODUTO - 1] = '\0';
            vendas[num_produtos].quantidade_total = quantidade;
            num_produtos++;
        }
    }

    fclose(f);

    if (num_produtos == 0) {
        return -2;
    }

    int indice_max = 0;
    for (int i = 1; i < num_produtos; i++) {
        if (vendas[i].quantidade_total > vendas[indice_max].quantidade_total) {
            indice_max = i;
        }
    }

    snprintf(top_selling_product, tamanho_saida, "%s", vendas[indice_max].produto);
    return 0;
}