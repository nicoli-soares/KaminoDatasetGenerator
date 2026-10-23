#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int get_positive(const int *input, int n, int *output, int *out_len) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (input[i] > 0) {
            output[count++] = input[i];
        }
    }
    *out_len = count;
    return 0;
}

void test_positive_all_positive() {
    int arr[] = {-1, -2, 4, 5, 6};
    int out[5];
    int out_len;
    get_positive(arr, 5, out, &out_len);
    assert(out_len == 3);
    assert(out[0] == 4 && out[1] == 5 && out[2] == 6);
}

void test_positive_mixed() {
    int arr[] = {5, 3, -5, 2, 3, 3, 9, 0, 123, 1, -10};
    int out[11];
    int out_len;
    get_positive(arr, 11, out, &out_len);
    assert(out_len == 8);
    int expected[] = {5, 3, 2, 3, 3, 9, 123, 1};
    for (int i = 0; i < out_len; i++) {
        assert(out[i] == expected[i]);
    }
}

void test_positive_all_negative() {
    int arr[] = {-1, -2};
    int out[2];
    int out_len;
    get_positive(arr, 2, out, &out_len);
    assert(out_len == 0);
}

void test_positive_empty() {
    int arr[] = { };
    int out[1];
    int out_len;
    get_positive(arr, 0, out, &out_len);
    assert(out_len == 0);
}

int main() {
    test_positive_all_positive();
    test_positive_mixed();
    test_positive_all_negative();
    test_positive_empty();
    return 0;
}