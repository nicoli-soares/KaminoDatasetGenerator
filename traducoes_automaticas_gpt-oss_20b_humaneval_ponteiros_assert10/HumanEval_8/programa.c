#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    int sum;
    int product;
} SumProductResult;

int sum_product(const int *numbers, int n, int *sum, int *product) {
    *sum = 0;
    *product = 1;
    for (int i = 0; i < n; ++i) {
        *sum += numbers[i];
        *product *= numbers[i];
    }
    return 0;
}

void test_sum_product_empty() {
    int sum, product;
    sum_product(NULL, 0, &sum, &product);
    assert(sum == 0);
    assert(product == 1);
}

void test_sum_product_all_ones() {
    int arr[] = {1, 1, 1};
    int sum, product;
    sum_product(arr, 3, &sum, &product);
    assert(sum == 3);
    assert(product == 1);
}

void test_sum_product_mix() {
    int arr[] = {100, 0};
    int sum, product;
    sum_product(arr, 2, &sum, &product);
    assert(sum == 100);
    assert(product == 0);
}

void test_sum_product_arbitrary() {
    int arr[] = {3, 5, 7};
    int sum, product;
    sum_product(arr, 3, &sum, &product);
    assert(sum == 15);
    assert(product == 105);
}

void test_sum_product_single() {
    int arr[] = {10};
    int sum, product;
    sum_product(arr, 1, &sum, &product);
    assert(sum == 10);
    assert(product == 10);
}

int main(void) {
    test_sum_product_empty();
    test_sum_product_all_ones();
    test_sum_product_mix();
    test_sum_product_arbitrary();
    test_sum_product_single();
    return 0;
}