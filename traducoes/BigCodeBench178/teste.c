#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* ============================================================
   FUNCAO (equivalente ao "original_code" em Python)
   ============================================================ */

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

/* ============================================================
   TESTES (traduzidos do campo "test" real do BigCodeBench/178)
   ============================================================ */

void test_case_1() {
    // {'ip': '192.168.1.1'} -> IP valido, devolve o proprio IP
    char saida[256];
    task_func("{\"ip\": \"192.168.1.1\"}", saida, sizeof(saida));
    assert(strcmp(saida, "192.168.1.1") == 0);
    printf("test_case_1 passou! resultado: %s\n", saida);
}

void test_case_2() {
    // {'ip': '500.500.500.500'} -> formato bate (mesmo com numeros invalidos),
    // entao devolve o proprio texto - igual ao comportamento do Python original
    char saida[256];
    task_func("{\"ip\": \"500.500.500.500\"}", saida, sizeof(saida));
    assert(strcmp(saida, "500.500.500.500") == 0);
    printf("test_case_2 passou! resultado: %s\n", saida);
}

void test_case_3() {
    // {'ip': '192.168.0.3'} -> IP valido
    char saida[256];
    task_func("{\"ip\": \"192.168.0.3\"}", saida, sizeof(saida));
    assert(strcmp(saida, "192.168.0.3") == 0);
    printf("test_case_3 passou! resultado: %s\n", saida);
}

void test_case_4() {
    // {'ip': ''} -> string vazia nao bate com o formato de IP
    char saida[256];
    task_func("{\"ip\": \"\"}", saida, sizeof(saida));
    assert(strcmp(saida, "Invalid IP address received") == 0);
    printf("test_case_4 passou! resultado: %s\n", saida);
}

void test_case_5() {
    // {'ip': 'Non-JSON response'} -> texto nao numerico, invalido
    char saida[256];
    task_func("{\"ip\": \"Non-JSON response\"}", saida, sizeof(saida));
    assert(strcmp(saida, "Invalid IP address received") == 0);
    printf("test_case_5 passou! resultado: %s\n", saida);
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