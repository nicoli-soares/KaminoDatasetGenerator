#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

typedef struct {
    int sum;
    int product;
} SumProduct;

SumProduct sum_product(int numbers[], int count) {
    SumProduct result = {0, 1};
    for (int i = 0; i < count; i++) {
        result.sum += numbers[i];
        result.product *= numbers[i];
    }
    return result;
}

void check(SumProduct (*candidate)(int *, int)) {
    int empty[] = {};
    SumProduct result_empty = candidate(empty, 0);
    assert(result_empty.sum == 0 && result_empty.product == 1);

    int ones[] = {1, 1, 1};
    SumProduct result_ones = candidate(ones, 3);
    assert(result_ones.sum == 3 && result_ones.product == 1);

    int values[] = {100, 0};
    SumProduct result_values = candidate(values, 2);
    assert(result_values.sum == 100 && result_values.product == 0);

    int numbers[] = {3, 5, 7};
    SumProduct result_numbers = candidate(numbers, 3);
    assert(result_numbers.sum == 15 && result_numbers.product == 105);

    int single[] = {10};
    SumProduct result_single = candidate(single, 1);
    assert(result_single.sum == 10 && result_single.product == 10);
}

int main() {
    check(sum_product);
    printf("All tests passed!\n");
    return 0;
}