typedef struct {
    int valor;
} Numero;

typedef struct {
    int soma;
    int produto;
} Resultado;

Resultado sum_product_c(Numero *numbers, int n) {
    Resultado result = {0, 1};

    for (int i = 0; i < n; i++) {
        result.soma += numbers[i].valor;
        result.produto *= numbers[i].valor;
    }

    return result;
}

void test_sum_product_c() {
    Numero numbers1[] = {};
    Numero numbers2[] = {{1, 1, 1}, {100, 0}, {3, 5, 7}, {10}};
    int expected1[] = {0, 1};
    int expected2[] = {3, 1, 100, 0, 15, 105, 10};
    int sizes[] = {0, 3, 2, 3, 1};

    for (int i = 0; i < 5; i++) {
        Resultado result = sum_product_c(numbers2 + (i * 3), sizes[i]);
        assert(result.soma == expected2[i * 2]);
        assert(result.produto == expected2[i * 2 + 1]);
    }
}

int main() {
    test_sum_product_c();
    return 0;
}