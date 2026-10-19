typedef struct {
    int *dados;
    size_t tamanho;
} Resultado;

Resultado intersperse(int numbers[], size_t tamanho, int delimiter) {
    if (tamanho == 0) {
        return (Resultado){NULL, 0};
    }

    size_t result_size = 2 * (tamanho - 1) + 1;
    int *result = malloc(result_size * sizeof(int));

    if (!result) {
        return (Resultado){NULL, 0};
    }

    for (size_t i = 0; i < tamanho - 1; i++) {
        result[2 * i] = numbers[i];
        result[2 * i + 1] = delimiter;
    }

    result[2 * (tamanho - 1)] = numbers[tamanho - 1];

    return (Resultado){result, result_size};
}

void test_case_1() {
    int numbers[] = {};
    Resultado res = intersperse(numbers, 0, 7);
    assert(res.tamanho == 0);
}

void test_case_2() {
    int numbers[] = {5, 6, 3, 2};
    Resultado res = intersperse(numbers, 4, 8);
    assert(res.tamanho == 7);
    assert(res.dados[0] == 5);
    assert(res.dados[1] == 8);
    assert(res.dados[2] == 6);
    assert(res.dados[3] == 8);
    assert(res.dados[4] == 3);
    assert(res.dados[5] == 8);
    assert(res.dados[6] == 2);
}

void test_case_3() {
    int numbers[] = {2, 2, 2};
    Resultado res = intersperse(numbers, 3, 2);
    assert(res.tamanho == 5);
    assert(res.dados[0] == 2);
    assert(res.dados[1] == 2);
    assert(res.dados[2] == 2);
    assert(res.dados[3] == 2);
    assert(res.dados[4] == 2);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}