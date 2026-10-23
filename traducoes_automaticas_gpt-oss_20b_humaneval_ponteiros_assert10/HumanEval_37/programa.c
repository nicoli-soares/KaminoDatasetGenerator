#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int sort_even(const int *input, int len, int *output) {
    int evens_count = (len + 1) / 2;
    int odds_count  = len / 2;
    int evens[evens_count];
    int odds[odds_count];
    int ei = 0, oi = 0;

    /* Extract even-indexed values */
    for (int i = 0; i < len; i += 2) {
        evens[ei++] = input[i];
    }
    /* Extract odd-indexed values */
    for (int i = 1; i < len; i += 2) {
        odds[oi++] = input[i];
    }

    /* Sort evens in ascending order (simple bubble sort) */
    for (int i = 0; i < evens_count - 1; i++) {
        for (int j = i + 1; j < evens_count; j++) {
            if (evens[i] > evens[j]) {
                int tmp = evens[i];
                evens[i] = evens[j];
                evens[j] = tmp;
            }
        }
    }

    /* Build the result array */
    int pos = 0;
    int min = evens_count < odds_count ? evens_count : odds_count;
    for (int i = 0; i < min; i++) {
        output[pos++] = evens[i];
        output[pos++] = odds[i];
    }
    if (evens_count > odds_count) {
        output[pos++] = evens[evens_count - 1];
    }
    return 0;
}

/* Test functions */
void test_sort_even() {
    /* Test 1 */
    int input1[] = {1, 2, 3};
    int out1[3];
    sort_even(input1, 3, out1);
    int expected1[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        assert(out1[i] == expected1[i]);
    }

    /* Test 2 */
    int input2[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int out2[11];
    sort_even(input2, 11, out2);
    int expected2[] = {-10, 3, -5, 2, -3, 3, 5, 0, 9, 1, 123};
    for (int i = 0; i < 11; i++) {
        assert(out2[i] == expected2[i]);
    }

    /* Test 3 */
    int input3[] = {5, 8, -12, 4, 23, 2, 3, 11, 12, -10};
    int out3[10];
    sort_even(input3, 10, out3);
    int expected3[] = {-12, 8, 3, 4, 5, 2, 12, 11, 23, -10};
    for (int i = 0; i < 10; i++) {
        assert(out3[i] == expected3[i]);
    }
}

int main(void) {
    test_sort_even();
    return 0;
}