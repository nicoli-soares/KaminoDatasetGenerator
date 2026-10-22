typedef struct {
    int sum;
    int product;
} SumProduct;

SumProduct sum_product_c(const int *numbers, int n) {
    SumProduct result = {0, 1};
    if (n == 0) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result.sum += numbers[i];
        result.product *= numbers[i];
    }
    return result;
}

void test_sum_product_c() {
    // Test empty list
    int empty[] = {};
    SumProduct res1 = sum_product_c(empty, 0);
    assert(res1.sum == 0 && res1.product == 1);

    // Test single element
    int single[] = {10};
    SumProduct res2 = sum_product_c(single, 1);
    assert(res2.sum == 10 && res2.product == 10);

    // Test multiple elements
    int multiple[] = {3, 5, 7};
    SumProduct res3 = sum_product_c(multiple, 3);
    assert(res3.sum == 3+5+7 && res3.product == 3*5*7);

    // Test with zero
    int with_zero[] = {100, 0};
    SumProduct res4 = sum_product_c(with_zero, 2);
    assert(res4.sum == 100 && res4.product == 0);

    // Test all ones
    int ones[] = {1, 1, 1};
    SumProduct res5 = sum_product_c(ones, 3);
    assert(res5.sum == 3 && res5.product == 1);
}

int main() {
    test_sum_product_c();
    return 0;
}