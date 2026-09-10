#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*  Codigos de retorno (equivalentes as excecoes do Python):
    0  -> sucesso
    -1  -> arquivo nao encontrado (equivalente ao FileNotFoundError)
    -2  -> nenhum dado de venda encontrado (equivalente ao ValueError do max() quando a sequencia esta vazia)
    -3  -> quantidade invalida, nao numerica (equivalente ao ValueError do int() quando a conversao falha)
  */

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

int task_func(const char *csv_file_path, char *top_selling_product, size_t tamanho_saida) {
    FILE *f = fopen(csv_file_path, "r");
    if (f == NULL) {
        return -1; // FileNotFoundError
    }

    char linha[MAX_LINHA];

    // Pula o cabecalho
    if (fgets(linha, sizeof(linha), f) == NULL) {
        fclose(f);
        return -2; // arquivo totalmente vazio, sem nem cabecalho
    }

    VendaProduto vendas[MAX_PRODUTOS];
    int num_produtos = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        remover_quebra_linha(linha);
        if (strlen(linha) == 0) continue; // ignora linhas em branco

        char *virgula = strchr(linha, ',');
        if (virgula == NULL) {
            fclose(f);
            return -3; // linha mal formatada
        }

        *virgula = '\0';
        const char *produto = linha;
        const char *quantidade_str = virgula + 1;

        char *endptr;
        long quantidade = strtol(quantidade_str, &endptr, 10);
        if (endptr == quantidade_str || *endptr != '\0') {
            fclose(f);
            return -3; // equivalente ao ValueError do int()
        }

        // Procura se o produto ja existe no array (equivalente ao defaultdict)
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
        return -2; // equivalente ao ValueError do max() em sequencia vazia
    }

    // Encontra o produto mais vendido
    int indice_max = 0, i;
    for (i = 1; i < num_produtos; i++) {
        if (vendas[i].quantidade_total > vendas[indice_max].quantidade_total) {
            indice_max = i;
        }
    }

    snprintf(top_selling_product, tamanho_saida, "%s", vendas[indice_max].produto);
    return 0;
}

void criar_csv(const char *caminho, const char *linhas[], int num_linhas) {
    FILE *f = fopen(caminho, "w");
    int i;
    for (i = 0; i < num_linhas; i++) {
        fprintf(f, "%s\n", linhas[i]);
    }
    fclose(f);
}

void test_case_1() {
    const char *linhas[] = {"product,quantity", "Product B,200", "Product A,100"};
    criar_csv("sales1.csv", linhas, 3);

    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("sales1.csv", resultado, sizeof(resultado));

    assert(status == 0);
    assert(strcmp(resultado, "Product B") == 0);
    printf("test_case_1 passou! resultado: %s\n", resultado);
}

void test_case_2() {
    const char *linhas[] = {"product,quantity", "Product Z,120", "Product Y,80"};
    criar_csv("sales2.csv", linhas, 3);

    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("sales2.csv", resultado, sizeof(resultado));

    assert(status == 0);
    assert(strcmp(resultado, "Product Z") == 0);
    printf("test_case_2 passou! resultado: %s\n", resultado);
}

void test_case_3() {
    const char *linhas[] = {"product,quantity", "Product M,500", "Product N,400"};
    criar_csv("sales3.csv", linhas, 3);

    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("sales3.csv", resultado, sizeof(resultado));

    assert(status == 0);
    assert(strcmp(resultado, "Product M") == 0);
    printf("test_case_3 passou! resultado: %s\n", resultado);
}

void test_case_4() {
    // Arquivo so com cabecalho, sem dados -> deve sinalizar erro
    const char *linhas[] = {"product,quantity"};
    criar_csv("sales4.csv", linhas, 1);

    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("sales4.csv", resultado, sizeof(resultado));

    assert(status == -2);
    printf("test_case_4 passou! (erro detectado: sem dados de venda)\n");
}

void test_case_5() {
    const char *linhas[] = {"product,quantity", "Single Product,999"};
    criar_csv("sales5.csv", linhas, 2);

    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("sales5.csv", resultado, sizeof(resultado));

    assert(status == 0);
    assert(strcmp(resultado, "Single Product") == 0);
    printf("test_case_5 passou! resultado: %s\n", resultado);
}

void test_case_6() {
    // Arquivo que nao existe -> deve sinalizar erro
    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("nonexistent.csv", resultado, sizeof(resultado));

    assert(status == -1);
    printf("test_case_6 passou! (erro detectado: arquivo nao encontrado)\n");
}

void test_case_7() {
    // Quantidade nao numerica -> deve sinalizar erro
    const char *linhas[] = {"product,quantity", "Product A,one hundred"};
    criar_csv("sales6.csv", linhas, 2);

    char resultado[MAX_NOME_PRODUTO];
    int status = task_func("sales6.csv", resultado, sizeof(resultado));

    assert(status == -3);
    printf("test_case_7 passou! (erro detectado: quantidade invalida)\n");
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    test_case_7();
    printf("\nTodos os testes passaram!\n");
    return 0;
}