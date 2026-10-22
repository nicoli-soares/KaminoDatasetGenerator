typedef struct {
    float valor;
} Numero;

float calcular_desvio_absoluto_medio(float *valores, int n) {
    float soma = 0.0f;
    for (int i = 0; i < n; i++) {
        soma += valores[i];
    }
    float media = soma / n;
    float total_desvio = 0.0f;
    for (int i = 0; i < n; i++) {
        total_desvio += fabsf(valores[i] - media);
    }
    return total_desvio / n;
}

void testar_desvio_absoluto_medio() {
    float valores1[] = {1.0f, 2.0f, 3.0f};
    int n1 = 3;
    assert(fabsf(calcular_desvio_absoluto_medio(valores1, n1) - (2.0f/3.0f)) < 1e-6f);

    float valores2[] = {1.0f, 2.0f, 3.0f, 4.0f};
    int n2 = 4;
    assert(fabsf(calcular_desvio_absoluto_medio(valores2, n2) - 1.0f) < 1e-6f);

    float valores3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    int n3 = 5;
    assert(fabsf(calcular_desvio_absoluto_medio(valores3, n3) - (6.0f/5.0f)) < 1e-6f);
}

int main() {
    testar_desvio_absoluto_medio();
    return 0;
}