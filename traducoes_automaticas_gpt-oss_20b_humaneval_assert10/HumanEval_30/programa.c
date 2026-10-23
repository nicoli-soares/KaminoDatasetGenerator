#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Structs and helper functions */
typedef struct {
    const int *input;
    int input_len;
    const int *expected;
    int expected_len;
} TestCase;

bool arrays_equal(const int *a, int len_a, const int *b, int len_b) {
    if (len_a != len_b) return false;
    for (int i = 0; i < len_a; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/* Core function */
int get_positive_c(const int *l, int len, int *out, int *out_len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (l[i] > 0) {
            out[count++] = l[i];
        }
    }
    *out_len = count;
    return 0; /* success */
}

/* Test functions */
void test_get_positive(void) {
    /* Test case 1 */
    int input1[] = { -1, -2, 4, 5, 6 };
    int expected1[] = { 4, 5, 6 };
    int out1[5];
    int out_len1;
    get_positive_c(input1, 5, out1, &out_len1);
    assert(arrays_equal(out1, out_len1, expected1, 3));

    /* Test case 2 */
    int input2[] = { 5, 3, -5, 2, 3, 3, 9, 0, 123, 1, -10 };
    int expected2[] = { 5, 3, 2, 3, 3, 9, 123, 1 };
    int out2[11];
    int out_len2;
    get_positive_c(input2, 11, out2, &out_len2);
    assert(arrays_equal(out2, out_len2, expected2, 8));

    /* Test case 3 */
    int input3[] = { -1, -2 };
    int expected3[] = { };
    int out3[2];
    int out_len3;
    get_positive_c(input3, 2, out3, &out_len3);
    assert(arrays_equal(out3, out_len3, expected3, 0));

    /* Test case 4 */
    int input4[] = { };
    int expected4[] = { };
    int out4[0];
    int out_len4;
    get_positive_c(input4, 0, out4, &out_len4);
    assert(arrays_equal(out4, out_len4, expected4, 0));
}

/* Main execution */
int main(void) {
    test_get_positive();
    return 0;
}