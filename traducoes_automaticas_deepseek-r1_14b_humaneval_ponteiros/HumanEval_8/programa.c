typedef struct {
    int sum;
    int product;
} Result;

Result sum_product_c(int numbers[], int size) {
    Result result = {0, 1};  // Initialize sum to 0, product to 1

    if (size == 0 || numbers == NULL) {
        return result;
    }

    for (int i = 0; i < size; i++) {
        result.sum += numbers[i];
        result.product *= numbers[i];
    }

    return result;
}

void test_sum_product_empty() {
    Result result = sum_product_c(NULL, 0);
    assert(result.sum == 0 && result.product == 1);
}

void test_sum_product_single() {
    int numbers[] = {10};
    Result result = sum_product_c(numbers, 1);
    assert(result.sum == 10 && result.product == 10);
}

void test_sum_product_multiple() {
    int numbers[] = {3, 5, 7};
    Result result = sum_product_c(numbers, 3);
    assert(result.sum == 3 + 5 + 7 && result.product == 3 * 5 * 7);
}

void test_sum_product_zero() {
    int numbers[] = {100, 0};
    Result result = sum_product_c(numbers, 2);
    assert(result.sum == 100 && result.product == 0);
}

void test_sum_product_all_ones() {
    int numbers[] = {1, 1, 1};
    Result result = sum_product_c(numbers, 3);
    assert(result.sum == 3 && result.product == 1);
}

int main() {
    test_sum_product_empty();
    test_sum_product_single();
    test_sum_product_multiple();
    test_sum_product_zero();
    test_sum_product_all_ones();
    return 0;
}