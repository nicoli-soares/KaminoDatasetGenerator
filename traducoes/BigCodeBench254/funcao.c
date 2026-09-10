/*
Como C nao tem excecoes, usamos o valor de retorno para sinalizar erro:
retorno  0 -> sucesso, resultado escrito em 'output'
retorno -1 -> erro (equivalente ao ValueError do Python quando o numero e negativo - "math domain error")
*/
#include <stdio.h>
#include <string.h>
#include <math.h>

int task_func(double decimal_value, char *output, size_t output_size) {
    if (decimal_value < 0) {
        return -1;
    }

    double square_root = sqrt(decimal_value);

    // arredonda para 2 casas decimais (equivalente a round(x, 2) do Python)
    double arredondado = round(square_root * 100.0) / 100.0;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%.2f", arredondado);

    // Remove um zero a direita, mantendo pelo menos uma casa decimal
    // (equivalente a como o str() do Python formata floats: 1000.0 -> "1000.0", nao "1000.00")
    size_t len = strlen(buffer);
    if (len > 2 && buffer[len - 1] == '0' && buffer[len - 2] != '.') {
        buffer[len - 1] = '\0';
    }

    // Monta a string JSON: coloca aspas duplas ao redor do numero
    // (equivalente ao json.dumps(str(square_root)) do Python)
    snprintf(output, output_size, "\"%s\"", buffer);

    return 0;
}