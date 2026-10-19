#include <assert.h>

int sum_product_c(int *numbers, int size, int *sum, int *prod) {
    *sum = 0;
    *prod = 1;

    for (int i = 0; i < size; i++) {
        *sum += numbers[i];
        *prod *= numbers[i];
    }

    return 0;
}

int main() {
    int sum, prod;
    int result;

    // Teste 1
    result = sum_product_c(NULL, 0, &sum, &prod);
    assert(result == 0 && sum == 0 && prod == 1);

    // Teste 2
    result = sum_product_c(NULL, 3, &sum, &prod);
    assert(result == 0 && sum == 3 && prod == 1);

    // Teste 3
    int nums1[] = {100, 0};
    result = sum_product_c(nums1, 2, &sum, &prod);
    assert(result == 0 && sum == 100 && prod == 0);

    // Teste 4
    int nums2[] = {3, 5, 7};
    result = sum_product_c(nums2, 3, &sum, &prod);
    assert(result == 0 && sum == 15 && prod == 105);

    // Teste 5
    int nums3[] = {10};
    result = sum_product_c(nums3, 1, &sum, &prod);
    assert(result == 0 && sum == 10 && prod == 10);

    printf("Todos os testes passaram com sucesso!\n");
    return 0;
}