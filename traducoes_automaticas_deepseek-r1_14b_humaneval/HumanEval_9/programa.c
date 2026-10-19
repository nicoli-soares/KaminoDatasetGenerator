#include <assert.h>
#include <stdio.h>

int* rolling_max(int* numbers, int n) {
    if (n == 0) {
        return NULL;
    }
    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    int running_max = numbers[0];
    result[0] = running_max;
    for (int i = 1; i < n; i++) {
        if (numbers[i] > running_max) {
            running_max = numbers[i];
        }
        result[i] = running_max;
    }
    return result;
}

void test_empty_list() {
    int* empty = rolling_max(NULL, 0);
    assert(empty == NULL);
}

void test_increasing_sequence() {
    int nums[] = {1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(int);
    int* result = rolling_max(nums, n);
    assert(result != NULL);
    assert(result[0] == 1);
    assert(result[1] == 2);
    assert(result[2] == 3);
    assert(result[3] == 4);
    free(result);
}

void test_decreasing_sequence() {
    int nums[] = {4, 3, 2, 1};
    int n = sizeof(nums) / sizeof(int);
    int* result = rolling_max(nums, n);
    assert(result != NULL);
    assert(result[0] == 4);
    assert(result[1] == 4);
    assert(result[2] == 4);
    assert(result[3] == 4);
    free(result);
}

void test_peak_in_middle() {
    int nums[] = {3, 2, 3, 100, 3};
    int n = sizeof(nums) / sizeof(int);
    int* result = rolling_max(nums, n);
    assert(result != NULL);
    assert(result[0] == 3);
    assert(result[1] == 3);
    assert(result[2] == 3);
    assert(result[3] == 100);
    assert(result[4] == 100);
    free(result);
}

int main() {
    test_empty_list();
    test_increasing_sequence();
    test_decreasing_sequence();
    test_peak_in_middle();
    return 0;
}