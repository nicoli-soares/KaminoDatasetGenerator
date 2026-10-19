#include <assert.h>
#include <math.h>

typedef struct {
    float valor;
} Numero;

float sum_array(const Numero *valores, int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += valores[i].valor;
    }
    return total;
}

float mean_absolute_deviation_c(const Numero *numbers, int n) {
    float mean = sum_array(numbers, n) / n;
    float total_deviation = 0;
    for (int i = 0; i < n; i++) {
        total_deviation += abs(numbers[i].valor - mean);
    }
    return total_deviation / n;
}

void test_mean_absolute_deviation_c() {
    Numero numbers1[] = {{1.0}, {2.0}, {3.0}, {4.0}};
    assert(fabs(mean_absolute_deviation_c(numbers1, 4) - 1.0) < 1e-6);

    Numero numbers2[] = {{1.0}, {2.0}, {3.0}};
    assert(fabs(mean_absolute_deviation_c(numbers2, 3) - 2.0 / 3.0) < 1e-6);

    Numero numbers3[] = {{1.0}, {2.0}, {3.0}, {4.0}, {5.0}};
    assert(fabs(mean_absolute_deviation_c(numbers3, 5) - 6.0 / 5.0) < 1e-6);
}

int main() {
    test_mean_absolute_deviation_c();
    return 0;
}