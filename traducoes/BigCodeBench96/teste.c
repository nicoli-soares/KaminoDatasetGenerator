#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_PALAVRA 128
#define MAX_PALAVRAS_DISTINTAS 256
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
int task_func(const char *csv_file, char csv_delimiter, ContagemPalavraCSV *resultado, int *tamanho_resultado) {
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

void criar_arquivo(const char *caminho, const char *conteudo) {
    FILE *f = fopen(caminho, "w");
    fputs(conteudo, f);
    fclose(f);
}

int buscar_contagem_csv(ContagemPalavraCSV *resultado, int tamanho, const char *palavra) {
    int i;
    for ( i = 0; i < tamanho; i++) {
        if (strcmp(resultado[i].palavra, palavra) == 0) {
            return resultado[i].contagem;
        }
    }
    return -1; // nao encontrado
}

void test_word_count() {
    // "word1\nword2\nword1" com delimitador ',' -> espera word1:2, word2:1
    criar_arquivo("dummy1.csv", "word1\nword2\nword1");

    ContagemPalavraCSV resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho;
    int status = task_func("dummy1.csv", ',', resultado, &tamanho);

    assert(status == 0);
    assert(buscar_contagem_csv(resultado, tamanho, "word1") == 2);
    assert(buscar_contagem_csv(resultado, tamanho, "word2") == 1);
    printf("test_word_count passou!\n");
}

void test_empty_file() {
    // arquivo vazio -> resultado deve ter tamanho 0
    criar_arquivo("dummy2.csv", "");

    ContagemPalavraCSV resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho;
    int status = task_func("dummy2.csv", ',', resultado, &tamanho);

    assert(status == 0);
    assert(tamanho == 0);
    printf("test_empty_file passou!\n");
}

void test_no_repeated_words() {
    // "word1,word2,word3" -> cada palavra aparece 1 vez
    criar_arquivo("dummy3.csv", "word1,word2,word3");

    ContagemPalavraCSV resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho;
    int status = task_func("dummy3.csv", ',', resultado, &tamanho);

    assert(status == 0);
    assert(buscar_contagem_csv(resultado, tamanho, "word1") == 1);
    assert(buscar_contagem_csv(resultado, tamanho, "word2") == 1);
    assert(buscar_contagem_csv(resultado, tamanho, "word3") == 1);
    printf("test_no_repeated_words passou!\n");
}

void test_custom_delimiter() {
    // "word1;word2;word1" com delimitador ';' -> espera word1:2, word2:1
    criar_arquivo("dummy4.csv", "word1;word2;word1");

    ContagemPalavraCSV resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho;
    int status = task_func("dummy4.csv", ';', resultado, &tamanho);

    assert(status == 0);
    assert(buscar_contagem_csv(resultado, tamanho, "word1") == 2);
    assert(buscar_contagem_csv(resultado, tamanho, "word2") == 1);
    printf("test_custom_delimiter passou!\n");
}

void test_ordenacao_decrescente() {
    // Teste extra (nao do dataset original, mas valida a ordenacao que os
    // testes de dataset nao checam diretamente de forma isolada)
    criar_arquivo("dummy5.csv", "a,b,a,c,a,b");
    // a:3, b:2, c:1 -> ordem esperada: a, b, c

    ContagemPalavraCSV resultado[MAX_PALAVRAS_DISTINTAS];
    int tamanho;
    int status = task_func("dummy5.csv", ',', resultado, &tamanho);

    assert(status == 0);
    assert(tamanho == 3);
    assert(strcmp(resultado[0].palavra, "a") == 0 && resultado[0].contagem == 3);
    assert(strcmp(resultado[1].palavra, "b") == 0 && resultado[1].contagem == 2);
    assert(strcmp(resultado[2].palavra, "c") == 0 && resultado[2].contagem == 1);
    printf("test_ordenacao_decrescente passou!\n");
}

int main() {
    test_word_count();
    test_empty_file();
    test_no_repeated_words();
    test_custom_delimiter();
    test_ordenacao_decrescente();
    printf("\nTodos os testes passaram!\n");
    return 0;
}