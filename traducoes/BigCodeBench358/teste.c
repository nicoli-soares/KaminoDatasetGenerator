#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAX_ELEMENTO 32
#define MAX_ELEMENTOS 32
#define MAX_R 10
#define MAX_COMBINACOES 1000

typedef struct {
    char valores[MAX_R][MAX_ELEMENTO];
} Combinacao;

// Extrai os elementos de um array JSON (numeros ou strings) associado a uma chave
// Retorna 1 se encontrou e conseguiu parsear, 0 caso contrario
static int extrair_lista(const char *json_data, const char *chave,
                          char elementos[][MAX_ELEMENTO], int *n) {
    char busca[64];
    snprintf(busca, sizeof(busca), "\"%s\"", chave);

    const char *pos = strstr(json_data, busca);
    if (!pos) return 0;

    pos = strchr(pos, ':');
    if (!pos) return 0;
    pos++;
    while (*pos == ' ') pos++;
    if (*pos != '[') return 0;
    pos++;

    *n = 0;
    while (*pos != ']' && *pos != '\0') {
        while (*pos == ' ' || *pos == ',') pos++;
        if (*pos == ']') break;

        char valor[MAX_ELEMENTO];
        int i = 0;
        if (*pos == '"') {
            pos++;
            while (*pos != '"' && *pos != '\0' && i < MAX_ELEMENTO - 1) {
                valor[i++] = *pos++;
            }
            if (*pos == '"') pos++;
        } else {
            while (*pos != ',' && *pos != ']' && *pos != '\0' && i < MAX_ELEMENTO - 1) {
                valor[i++] = *pos++;
            }
        }
        valor[i] = '\0';

        if (*n < MAX_ELEMENTOS) {
            strcpy(elementos[*n], valor);
            (*n)++;
        }
    }
    return 1;
}

// Gera recursivamente as combinacoes de tamanho r (mesma logica da BigCodeBench/297,
// mas operando sobre strings genericas em vez de numeros)
static void gerar_combinacoes(char elementos[][MAX_ELEMENTO], int n, int r, char atual[][MAX_ELEMENTO], int pos_atual, int inicio, Combinacao *resultado, int *num_combinacoes) {
    int i;
    if (pos_atual == r) {
        for (i = 0; i < r; i++) {
            strcpy(resultado[*num_combinacoes].valores[i], atual[i]);
        }
        (*num_combinacoes)++;
        return;
    }

    for (i = inicio; i < n; i++) {
        strcpy(atual[pos_atual], elementos[i]);
        gerar_combinacoes(elementos, n, r, atual, pos_atual + 1, i + 1, resultado, num_combinacoes);
    }
}

// Funcao principal - equivalente ao task_func do Python
int task_func(const char *json_list, int r, Combinacao *resultado, int *num_combinacoes) {
    char elementos[MAX_ELEMENTOS][MAX_ELEMENTO];
    int n;

    if (!extrair_lista(json_list, "number_list", elementos, &n)) {
        return -1;
    }

    char atual[MAX_R][MAX_ELEMENTO];
    *num_combinacoes = 0;

    gerar_combinacoes(elementos, n, r, atual, 0, 0, resultado, num_combinacoes);

    return 0;
}

void imprimir_combinacao(Combinacao *c, int r) {
    printf("(");
    int i;
    for (i = 0; i < r; i++) {
        printf("%s%s", c->valores[i], (i < r - 1) ? ", " : "");
    }
    printf(")");
}

void test_case_1() {
    // {"number_list": [1,2,3,4,5]}, r=3
    Combinacao resultado[MAX_COMBINACOES];
    int num_combinacoes;
    int status = task_func("{\"number_list\": [1, 2, 3, 4, 5]}", 3, resultado, &num_combinacoes);

    assert(status == 0);
    assert(num_combinacoes == 10); // C(5,3) = 10

    // Confere a primeira e a ultima combinacao esperada
    assert(strcmp(resultado[0].valores[0], "1") == 0);
    assert(strcmp(resultado[0].valores[1], "2") == 0);
    assert(strcmp(resultado[0].valores[2], "3") == 0);

    assert(strcmp(resultado[9].valores[0], "3") == 0);
    assert(strcmp(resultado[9].valores[1], "4") == 0);
    assert(strcmp(resultado[9].valores[2], "5") == 0);

    printf("test_case_1 passou! (10 combinacoes geradas corretamente)\n");
}

void test_case_2() {
    // {"number_list": ["a","b","c"]}, r=2 -> lista de STRINGS, nao numeros!
    Combinacao resultado[MAX_COMBINACOES];
    int num_combinacoes;
    int status = task_func("{\"number_list\": [\"a\", \"b\", \"c\"]}", 2, resultado, &num_combinacoes);

    assert(status == 0);
    assert(num_combinacoes == 3); // ('a','b'), ('a','c'), ('b','c')

    assert(strcmp(resultado[0].valores[0], "a") == 0 && strcmp(resultado[0].valores[1], "b") == 0);
    assert(strcmp(resultado[1].valores[0], "a") == 0 && strcmp(resultado[1].valores[1], "c") == 0);
    assert(strcmp(resultado[2].valores[0], "b") == 0 && strcmp(resultado[2].valores[1], "c") == 0);

    printf("test_case_2 passou! (funciona com strings tambem, nao so numeros)\n");
}

void test_case_3() {
    // {"number_list": [1,2,3]}, r=1
    Combinacao resultado[MAX_COMBINACOES];
    int num_combinacoes;
    int status = task_func("{\"number_list\": [1, 2, 3]}", 1, resultado, &num_combinacoes);

    assert(status == 0);
    assert(num_combinacoes == 3);
    assert(strcmp(resultado[0].valores[0], "1") == 0);
    assert(strcmp(resultado[1].valores[0], "2") == 0);
    assert(strcmp(resultado[2].valores[0], "3") == 0);

    printf("test_case_3 passou!\n");
}

void test_case_4() {
    // '[]' (nao tem a chave "number_list") -> deve sinalizar erro
    Combinacao resultado[MAX_COMBINACOES];
    int num_combinacoes;
    int status = task_func("[]", 1, resultado, &num_combinacoes);

    assert(status == -1);
    printf("test_case_4 passou! (erro detectado corretamente)\n");
}

void test_case_5() {
    // {"number_list": [1,2]}, r=3 -> nenhuma combinacao possivel (lista vazia, sem erro)
    Combinacao resultado[MAX_COMBINACOES];
    int num_combinacoes;
    int status = task_func("{\"number_list\": [1, 2]}", 3, resultado, &num_combinacoes);

    assert(status == 0);
    assert(num_combinacoes == 0);

    printf("test_case_5 passou! (lista vazia, sem erro)\n");
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