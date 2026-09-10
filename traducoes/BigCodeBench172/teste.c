#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* ============================================================
   FUNCAO (equivalente ao "original_code" em Python)
   ============================================================ */
static int extrair_valor_string(const char *json_data, const char *chave,
                                 char *saida, size_t tamanho_saida) {
    char busca[64];
    snprintf(busca, sizeof(busca), "\"%s\"", chave);

    const char *pos = strstr(json_data, busca);
    if (pos == NULL) {
        return 0; // chave nao encontrada
    }

    // Avanca ate depois dos ":" que segue a chave
    pos = strchr(pos, ':');
    if (pos == NULL) return 0;
    pos++; // pula o ':'

    // Pula espacos em branco
    while (*pos == ' ') pos++;

    // Espera uma string entre aspas
    if (*pos != '"') return 0;
    pos++; // pula a aspa de abertura

    size_t i = 0;
    while (*pos != '"' && *pos != '\0' && i < tamanho_saida - 1) {
        saida[i++] = *pos++;
    }
    saida[i] = '\0';

    return 1;
}

// Calcula o dia da semana usando o algoritmo de Sakamoto.
// Retorna: 0 = domingo, 1 = segunda, ..., 6 = sabado
static int dia_da_semana_sakamoto(int ano, int mes, int dia) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (mes < 3) {
        ano -= 1;
    }
    return (ano + ano / 4 - ano / 100 + ano / 400 + t[mes - 1] + dia) % 7;
}

// Funcao principal - equivalente ao task_func do Python
int task_func(const char *json_data, int *eh_fim_de_semana) {
    char datetime_str[64];

    if (!extrair_valor_string(json_data, "utc_datetime", datetime_str, sizeof(datetime_str))) {
        return -1; // equivalente ao KeyError
    }

    int ano, mes, dia, hora, minuto, segundo;
    // Formato esperado: YYYY-MM-DDTHH:MM:SS
    int lidos = sscanf(datetime_str, "%d-%d-%dT%d:%d:%d",
                        &ano, &mes, &dia, &hora, &minuto, &segundo);
    if (lidos != 6) {
        return -1; // formato de data invalido
    }

    int dia_semana = dia_da_semana_sakamoto(ano, mes, dia);

    // 0 = domingo, 6 = sabado -> ambos sao fim de semana
    *eh_fim_de_semana = (dia_semana == 0 || dia_semana == 6);

    return 0;
}

/* ============================================================
   TESTES (traduzidos do campo "test" real do BigCodeBench/172)
   ============================================================ */

void test_case_1() {
    // Segunda-feira, 15 de abril de 2024 -> nao e fim de semana
    const char *json_data = "{\"utc_datetime\": \"2024-04-15T12:00:00\"}";
    int eh_fim_de_semana;
    int status = task_func(json_data, &eh_fim_de_semana);

    assert(status == 0);
    assert(eh_fim_de_semana == 0);
    printf("test_case_1 passou! (segunda-feira nao e fim de semana)\n");
}

void test_saturday() {
    // Sabado, 13 de abril de 2024 -> e fim de semana
    const char *json_data = "{\"utc_datetime\": \"2024-04-13T12:00:00\"}";
    int eh_fim_de_semana;
    int status = task_func(json_data, &eh_fim_de_semana);

    assert(status == 0);
    assert(eh_fim_de_semana == 1);
    printf("test_saturday passou! (sabado e fim de semana)\n");
}

void test_sunday() {
    // Domingo, 14 de abril de 2024 -> e fim de semana
    const char *json_data = "{\"utc_datetime\": \"2024-04-14T12:00:00\"}";
    int eh_fim_de_semana;
    int status = task_func(json_data, &eh_fim_de_semana);

    assert(status == 0);
    assert(eh_fim_de_semana == 1);
    printf("test_sunday passou! (domingo e fim de semana)\n");
}

void test_empty_json() {
    // JSON vazio {} -> deve sinalizar erro (equivalente ao KeyError)
    const char *json_data = "{}";
    int eh_fim_de_semana;
    int status = task_func(json_data, &eh_fim_de_semana);

    assert(status == -1);
    printf("test_empty_json passou! (erro detectado corretamente)\n");
}

void test_no_utc_datetime() {
    // JSON sem a chave 'utc_datetime' -> deve sinalizar erro
    const char *json_data = "{\"date\": \"2024-04-14T12:00:00\"}";
    int eh_fim_de_semana;
    int status = task_func(json_data, &eh_fim_de_semana);

    assert(status == -1);
    printf("test_no_utc_datetime passou! (erro detectado corretamente)\n");
}

int main() {
    test_case_1();
    test_saturday();
    test_sunday();
    test_empty_json();
    test_no_utc_datetime();
    printf("\nTodos os testes passaram!\n");
    return 0;
}