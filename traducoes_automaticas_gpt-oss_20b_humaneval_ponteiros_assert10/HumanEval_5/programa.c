#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Function that inserts a delimiter between every two consecutive elements of an integer array. */
int intersperse(const int *numbers, int n, int delimiter, int *out, int *out_len) {
    if (n == 0) {
        *out_len = 0;
        return 0; /* success, nothing to write */
    }

    *out_len = 2 * n - 1; /* n elements + (n-1) delimiters */

    int idx = 0;
    for (int i = 0; i < n - 1; i++) {
        out[idx++] = numbers[i];
        out[idx++] = delimiter;
    }
    out[idx] = numbers[n - 1]; /* last element */
    return 0; /* success */
}

/* Helper to compare two integer arrays for equality. */
void assert_arrays(const int *a, const int *b, int len) {
    for (int i = 0; i < len; i++) {
        assert(a[i] == b[i]);
    }
}

/* Test 1: Empty input list should return an empty result. */
void test_empty() {
    const int *numbers = NULL;
    int out_len = -1;
    int *out = NULL;
    intersperse(numbers, 0, 7, out, &out_len);
    assert(out_len == 0);
}

/* Test 2: Standard case with four elements. */
void test_standard() {
    int numbers[4] = {5, 6, 3, 2};
    int expected[7] = {5, 8, 6, 8, 3, 8, 2};
    int out[7];
    int out_len;
    intersperse(numbers, 4, 8, out, &out_len);
    assert(out_len == 7);
    assert_arrays(out, expected, 7);
}

/* Test 3: Input with repeated elements and same delimiter. */
void test_repeated() {
    int numbers[3] = {2, 2, 2};
    int expected[5] = {2, 2, 2, 2, 2};
    int out[5];
    int out_len;
    intersperse(numbers, 3, 2, out, &out_len);
    assert(out_len == 5);
    assert_arrays(out, expected, 5);
}

/* Main function to run all tests. */
int main(void) {
    test_empty();
    test_standard();
    test_repeated();
    /* If all asserts passed, program exits normally. */
    return 0;
}