#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float chave;
    float valor;
} ParesNumeros;

int has_close_elements_c(ParesNumeros* numbers, int size, float threshold) {
    for (int idx = 0; idx < size; idx++) {
        for (int idx2 = idx + 1; idx2 < size; idx2++) {
            float distance = fabs(numbers[idx].chave - numbers[idx2].chave);
            if (distance < threshold) {
                return 1;
            }
        }
    }
    return 0;
}

void test_has_close_elements_c() {
    ParesNumeros numbers1[] = {{1.0, 1.0}, {2.0, 2.0}, {3.9, 3.9}, {4.0, 4.0}, {5.0, 5.0}, {2.2, 2.2}};
    assert(has_close_elements_c(numbers1, 6, 0.3) == 1);
    assert(has_close_elements_c(numbers1, 6, 0.05) == 0);
    ParesNumeros numbers2[] = {{1.0, 1.0}, {2.0, 2.0}, {5.9, 5.9}, {4.0, 4.0}, {5.0, 5.0}};
    assert(has_close_elements_c(numbers2, 5, 0.95) == 1);
    assert(has_close_elements_c(numbers2, 5, 0.8) == 0);
    ParesNumeros numbers3[] = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}, {5.0, 5.0}, {2.0, 2.0}};
    assert(has_close_elements_c(numbers3, 6, 0.1) == 1);
    ParesNumeros numbers4[] = {{1.1, 1.1}, {2.2, 2.2}, {3.1, 3.1}, {4.1, 4.1}, {5.1, 5.1}};
    assert(has_close_elements_c(numbers4, 5, 1.0) == 1);
    assert(has_close_elements_c(numbers4, 5, 0.5) == 0);
}

int main() {
    test_has_close_elements_c();
    return 0;
}