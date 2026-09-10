#include <stdio.h>
#include <string.h>
#define MAX_PALAVRA 128
#define MAX_LINHA 1024

typedef struct {
    char palavra[MAX_PALAVRA];
    int contagem;
} ContagemPalavraCSV;

static void remover_quebra_linha(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

static void adicionar_palavra_csv(ContagemPalavraCSV *resultado, int *tamanho, const char *palavra) {
    int i;
    for ( i = 0; i < *tamanho; i++) {
        if (strcmp(resultado[i].palavra, palavra) == 0) {
            resultado[i].contagem++;
            return;
        }
    }
    strncpy(resultado[*tamanho].palavra, palavra, MAX_PALAVRA - 1);
    resultado[*tamanho].palavra[MAX_PALAVRA - 1] = '\0';
    resultado[*tamanho].contagem = 1;
    (*tamanho)++;
}

// Funcao principal - equivalente ao task_func do Python
int task_func(const char *csv_file, char csv_delimiter,ContagemPalavraCSV *resultado, int *tamanho_resultado) {
    FILE *f = fopen(csv_file, "r");
    if (f == NULL) {
        return -1;
    }

    *tamanho_resultado = 0;
    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), f) != NULL) {
        remover_quebra_linha(linha);
        if (strlen(linha) == 0) continue;

        char *inicio = linha;
        char *pos;
        while ((pos = strchr(inicio, csv_delimiter)) != NULL) {
            *pos = '\0';
            adicionar_palavra_csv(resultado, tamanho_resultado, inicio);
            inicio = pos + 1;
        }
        adicionar_palavra_csv(resultado, tamanho_resultado, inicio);
    }

    fclose(f);

    // Ordena por contagem decrescente (bubble sort - suficiente para o tamanho do dataset)
    int i, j;
    for ( i = 0; i < *tamanho_resultado - 1; i++) {
        for ( j = 0; j < *tamanho_resultado - 1 - i; j++) {
            if (resultado[j].contagem < resultado[j + 1].contagem) {
                ContagemPalavraCSV tmp = resultado[j];
                resultado[j] = resultado[j + 1];
                resultado[j + 1] = tmp;
            }
        }
    }

    return 0;
}