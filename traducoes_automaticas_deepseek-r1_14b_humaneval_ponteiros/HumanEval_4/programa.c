typedef struct {
    double valor;
} Numero_c;

double mean_absolute_deviation_c(double numeros[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += numeros[i];
    }
    double media = soma / n;
    double soma_abs_diff = 0.0;
    for (int i = 0; i < n; i++) {
        soma_abs_diff += fabs(numeros[i] - media);
    }
    return soma_abs_diff / n;
}

int test_case_1(double numeros[], int n, double esperado) {
    double result = mean_absolute_deviation_c(numeros, n);
    double epsilon = 1e-6;
    return fabs(result - esperado) < epsilon;
}

int test_case_2(double numeros[], int n, double esperado) {
    double result = mean_absolute_deviation_c(numeros, n);
    double epsilon = 1e-6;
    return fabs(result - esperado) < epsilon;
}

int test_case_3(double numeros[], int n, double esperado) {
    double result = mean_absolute_deviation_c(numeros, n);
    double epsilon = 1e-6;
    return fabs(result - esperado) < epsilon;
}

int main() {
    // Test case 1
    double numeros1[] = {1.0, 2.0, 3.0};
    int n1 = sizeof(numeros1) / sizeof(numeros1[0]);
    double esperado1 = 2.0 / 3.0;
    int passou1 = test_case_1(numeros1, n1, esperado1);
    
    // Test case 2
    double numeros2[] = {1.0, 2.0, 3.0, 4.0};
    int n2 = sizeof(numeros2) / sizeof(numeros2[0]);
    double esperado2 = 1.0;
    int passou2 = test_case_2(numeros2, n2, esperado2);
    
    // Test case 3
    double numeros3[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int n3 = sizeof(numeros3) / sizeof(numeros3[0]);
    double esperado3 = 6.0 / 5.0;
    int passou3 = test_case_3(numeros3, n3, esperado3);
    
    // Print results
    printf("Test case 1: %s\n", passou1 ? "Passed" : "Failed");
    printf("Test case 2: %s\n", passou2 ? "Passed" : "Failed");
    printf("Test case 3: %s\n", passou3 ? "Passed" : "Failed");
    
    return 0;
}