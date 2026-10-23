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
} Result;

int sum_product(const int *numbers, size_t length, int *sum_out, int *prod_out) {
    int sum = 0;
    int prod = 1;
    for (size_t i = 0; i < length; ++i) {
        sum += numbers[i];
        prod *= numbers[i];
    }
    *sum_out = sum;
    *prod_out = prod;
    return 0;
}

void test_sum_product(void) {
    int sum, prod;
    /* Test 1: Empty list */
    sum_product(NULL, 0, &sum, &prod);
    assert(sum == 0);
    assert(prod == 1);

    /* Test 2: [1, 1, 1] */
    int arr1[] = {1, 1, 1};
    sum_product(arr1, 3, &sum, &prod);
    assert(sum == 3);
    assert(prod == 1);

    /* Test 3: [100, 0] */
    int arr2[] = {100, 0};
    sum_product(arr2, 2, &sum, &prod);
    assert(sum == 100);
    assert(prod == 0);

    /* Test 4: [3, 5, 7] */
    int arr3[] = {3, 5, 7};
    sum_product(arr3, 3, &sum, &prod);
    assert(sum == 3 + 5 + 7);
    assert(prod == 3 * 5 * 7);

    /* Test 5: [10] */
    int arr4[] = {10};
    sum_product(arr4, 1, &sum, &prod);
    assert(sum == 10);
    assert(prod == 10);
}

int main(void) {
    test_sum_product();
    return 0;
}