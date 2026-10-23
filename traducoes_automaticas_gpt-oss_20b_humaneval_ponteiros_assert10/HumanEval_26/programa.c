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
    int key;
    int value;
} CountEntry;

int remove_duplicates(const int *numbers, int n, int *out_numbers, int *out_size) {
    CountEntry counts[n];
    int counts_size = 0;

    for (int i = 0; i < n; i++) {
        int val = numbers[i];
        int found = 0;
        for (int j = 0; j < counts_size; j++) {
            if (counts[j].key == val) {
                counts[j].value++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[counts_size].key = val;
            counts[counts_size].value = 1;
            counts_size++;
        }
    }

    *out_size = 0;
    for (int i = 0; i < n; i++) {
        int val = numbers[i];
        int cnt = 0;
        for (int j = 0; j < counts_size; j++) {
            if (counts[j].key == val) {
                cnt = counts[j].value;
                break;
            }
        }
        if (cnt <= 1) {
            out_numbers[(*out_size)++] = val;
        }
    }

    return 0;
}

void assert_int_array_equals(const int *arr1, int len1, const int *arr2, int len2) {
    assert(len1 == len2);
    for (int i = 0; i < len1; i++) {
        assert(arr1[i] == arr2[i]);
    }
}

int main(void) {
    // Test 1: Empty list
    int input1[1] = {0}; // unused when n == 0
    int n1 = 0;
    int *output1 = (int *)malloc(n1 * sizeof(int));
    int outsize1;
    assert(remove_duplicates(input1, n1, output1, &outsize1) == 0);
    int expected1[1] = {0};
    assert_int_array_equals(output1, outsize1, expected1, 0);
    free(output1);

    // Test 2: No duplicates
    int input2[] = {1, 2, 3, 4};
    int n2 = sizeof(input2) / sizeof(input2[0]);
    int *output2 = (int *)malloc(n2 * sizeof(int));
    int outsize2;
    assert(remove_duplicates(input2, n2, output2, &outsize2) == 0);
    int expected2[] = {1, 2, 3, 4};
    assert_int_array_equals(output2, outsize2, expected2, n2);
    free(output2);

    // Test 3: Some duplicates
    int input3[] = {1, 2, 3, 2, 4, 3, 5};
    int n3 = sizeof(input3) / sizeof(input3[0]);
    int *output3 = (int *)malloc(n3 * sizeof(int));
    int outsize3;
    assert(remove_duplicates(input3, n3, output3, &outsize3) == 0);
    int expected3[] = {1, 4, 5};
    assert_int_array_equals(output3, outsize3, expected3, 3);
    free(output3);

    return 0;
}