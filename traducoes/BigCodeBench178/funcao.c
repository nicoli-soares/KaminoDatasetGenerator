#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Extrai o valor de uma chave string simples de um JSON "plano"
// (mesma abordagem usada na BigCodeBench/172)
static int extrair_valor_string(const char *json_data, const char *chave,
                                 char *saida, size_t tamanho_saida) {
    char busca[64];
    snprintf(busca, sizeof(busca), "\"%s\"", chave);

    const char *pos = strstr(json_data, busca);
    if (pos == NULL) {
        return 0;
    }

    pos = strchr(pos, ':');
    if (pos == NULL) return 0;
    pos++;

    while (*pos == ' ') pos++;

    if (*pos != '"') return 0;
    pos++;

    size_t i = 0;
    while (*pos != '"' && *pos != '\0' && i < tamanho_saida - 1) {
        saida[i++] = *pos++;
    }
    saida[i] = '\0';

    return 1;
}

// Verifica se uma string "parece" um endereco IP:
// numeros separados por 3 pontos (equivalente ao regex [0-9]+(?:\.[0-9]+){3})
// Nota: assim como o regex original (usado com re.match, sem ancorar o fim
// da string), esta funcao so confere o INICIO da string - e nao valida se
// os numeros estao no intervalo 0-255 de um IP real.
static int parece_ip(const char *s) {
    const char *p = s;
    int grupo;
    for (grupo = 0; grupo < 4; grupo++) {
        if (!isdigit((unsigned char)*p)) {
            return 0; // precisa de pelo menos um digito no grupo
        }
        while (isdigit((unsigned char)*p)) p++;

        if (grupo < 3) {
            if (*p != '.') {
                return 0;
            }
            p++;
        }
    }
    return 1;
}

// Funcao principal - equivalente ao task_func do Python
// Assim como em Python (onde qualquer excecao e capturada e devolvida
// como texto), esta funcao SEMPRE escreve um resultado em 'saida' -
// nunca "falha" do ponto de vista de quem chama.
void task_func(const char *json_data, char *saida, size_t tamanho_saida) {
    char ip[64];

    if (!extrair_valor_string(json_data, "ip", ip, sizeof(ip))) {
        // Equivalente ao "str(e)" do Python quando a chave 'ip' nao existe
        // (Python mostraria algo como "'ip'", a representacao de um KeyError)
        snprintf(saida, tamanho_saida, "'ip'");
        return;
    }

    if (parece_ip(ip)) {
        snprintf(saida, tamanho_saida, "%s", ip);
    } else {
        snprintf(saida, tamanho_saida, "Invalid IP address received");
    }
}