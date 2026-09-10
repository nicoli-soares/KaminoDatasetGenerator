#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

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

void test_case_1() {
    // Decimal('4.0') -> sqrt = 2.0 -> "2.0"
    char output[64];
    int status = task_func(4.0, output, sizeof(output));
    assert(status == 0);
    assert(strcmp(output, "\"2.0\"") == 0);
    printf("test_case_1 passou! resultado: %s\n", output);
}

void test_case_2() {
    // Decimal('0.0') -> sqrt = 0.0 -> "0.0"
    char output[64];
    int status = task_func(0.0, output, sizeof(output));
    assert(status == 0);
    assert(strcmp(output, "\"0.0\"") == 0);
    printf("test_case_2 passou! resultado: %s\n", output);
}

void test_case_3() {
    // Decimal('0.0001') -> sqrt = 0.01 -> "0.01"
    char output[64];
    int status = task_func(0.0001, output, sizeof(output));
    assert(status == 0);
    assert(strcmp(output, "\"0.01\"") == 0);
    printf("test_case_3 passou! resultado: %s\n", output);
}

void test_case_4() {
    // Decimal('1000000.0') -> sqrt = 1000.0 -> "1000.0"
    char output[64];
    int status = task_func(1000000.0, output, sizeof(output));
    assert(status == 0);
    assert(strcmp(output, "\"1000.0\"") == 0);
    printf("test_case_4 passou! resultado: %s\n", output);
}

void test_case_5() {
    // Decimal('-1.0') -> deve sinalizar erro (equivalente ao ValueError do Python)
    char output[64];
    int status = task_func(-1.0, output, sizeof(output));
    assert(status == -1);
    printf("test_case_5 passou! (erro detectado corretamente para valor negativo)\n");
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