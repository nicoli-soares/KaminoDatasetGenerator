typedef struct {
    float valor;
} Numero;

typedef struct {
    float media;
    float soma_abs_diff;
} Resultado;

float mean_absolute_deviation_c(float *numbers, int length) {
    float sum = 0.0;
    float mean = 0.0;
    float soma_abs_diff = 0.0;
    
    for (int i = 0; i < length; i++) {
        sum += numbers[i];
    }
    mean = sum / length;

    for (int i = 0; i < length; i++) {
        soma_abs_diff += fabs(numbers[i] - mean);
    }

    return soma_abs_diff / length;
}

void test_mean_absolute_deviation_c() {
    float numbers1[] = {1.0, 2.0, 3.0};
    float expected1 = 2.0 / 3.0;
    assert(fabs(mean_absolute_deviation_c(numbers1, 3) - expected1) < 1e-6);

    float numbers2[] = {1.0, 2.0, 3.0, 4.0};
    float expected2 = 1.0;
    assert(fabs(mean_absolute_deviation_c(numbers2, 4) - expected2) < 1e-6);

    float numbers3[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    float expected3 = 6.0 / 5.0;
    assert(fabs(mean_absolute_deviation_c(numbers3, 5) - expected3) < 1e-6);
}

int main() {
    test_mean_absolute_deviation_c();
    return 0;
}