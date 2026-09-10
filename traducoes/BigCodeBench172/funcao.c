#include <stdio.h>
#include <string.h>

// Extrai o valor de uma chave string simples de um JSON "plano"
// (nao usamos uma biblioteca JSON completa - extracao manual,
// suficiente para o formato simples usado nesta funcao)
// Retorna 1 se encontrou a chave, 0 se nao encontrou
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

// Retorna: 0 = domingo, 1 = segunda, ..., 6 = sabado
static int dia_da_semana_sakamoto(int ano, int mes, int dia) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (mes < 3) {
        ano -= 1;
    }
    return (ano + ano / 4 - ano / 100 + ano / 400 + t[mes - 1] + dia) % 7;
}

// Funcao principal - equivalente ao task_func do Python
// Retorna 0 em sucesso (resultado em *eh_fim_de_semana: 0 ou 1)
// Retorna -1 se a chave "utc_datetime" nao existir (equivalente ao KeyError)
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