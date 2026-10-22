#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct {
    int value;
} RollingMaxResult;

int* rolling_max_c(int* numbers, int len) {
    if (numbers == NULL || len == 0) {
        return NULL;
    }

    int* result = malloc(len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int running_max = numbers[0];
    result[0] = running_max;

    for (int i = 1; i < len; i++) {
        if (numbers[i] > running_max) {
            running_max = numbers[i];
        }
        result[i] = running_max;
    }

    return result;
}

void test_rolling_max() {
    // Test case 1: Empty input
    assert(rolling_max_c(NULL, 0) == NULL);

    // Test case 2: All increasing
    int test1[] = {1, 2, 3, 4};
    int expected1[] = {1, 2, 3, 4};
    int* result1 = rolling_max_c(test1, 4);
    for (int i = 0; i < 4; i++) {
        assert(result1[i] == expected1[i]);
    }
    free(result1);

    // Test case 3: All decreasing
    int test2[] = {4, 3, 2, 1};
    int expected2[] = {4, 4, 4, 4};
    int* result2 = rolling_max_c(test2, 4);
    for (int i = 0; i < 4; i++) {
        assert(result2[i] == expected2[i]);
    }
    free(result2);

    // Test case 4: Mixed values
    int test3[] = {3, 2, 3, 100, 3};
    int expected3[] = {3, 3, 3, 100, 100};
    int* result3 = rolling_max_c(test3, 5);
    for (int i = 0; i < 5; i++) {
        assert(result3[i] == expected3[i]);
    }
    free(result3);
}

int main() {
    test_rolling_max();
    return 0;
}