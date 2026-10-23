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
    int value;
} SortThirdStruct;

void sort_third(const int *in, int n, int *out) {
    int i;
    /* copy original array */
    for (i = 0; i < n; i++) {
        out[i] = in[i];
    }
    /* collect elements at indices divisible by 3 */
    int count = (n + 2) / 3;          /* ceil(n/3) */
    int values[count];
    int idx = 0;
    for (i = 0; i < n; i += 3) {
        values[idx++] = in[i];
    }
    /* simple bubble sort ascending */
    for (int a = 0; a < count - 1; a++) {
        for (int b = 0; b < count - a - 1; b++) {
            if (values[b] > values[b + 1]) {
                int tmp = values[b];
                values[b] = values[b + 1];
                values[b + 1] = tmp;
            }
        }
    }
    /* write sorted values back to output */
    idx = 0;
    for (i = 0; i < n; i += 3) {
        out[i] = values[idx++];
    }
}

int arrays_equal(const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void test_sort_third(void) {
    /* Test 1 */
    int input1[] = {1, 2, 3};
    int expected1[] = {1, 2, 3};
    int output1[3];
    sort_third(input1, 3, output1);
    assert(arrays_equal(output1, expected1, 3));

    /* Test 2 */
    int input2[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int expected2[] = {1, 3, -5, 2, -3, 3, 5, 0, 123, 9, -10};
    int output2[11];
    sort_third(input2, 11, output2);
    assert(arrays_equal(output2, expected2, 11));

    /* Test 3 */
    int input3[] = {5, 8, -12, 4, 23, 2, 3, 11, 12, -10};
    int expected3[] = {-10, 8, -12, 3, 23, 2, 4, 11, 12, 5};
    int output3[10];
    sort_third(input3, 10, output3);
    assert(arrays_equal(output3, expected3, 10));

    /* Test 4 */
    int input4[] = {5, 6, 3, 4, 8, 9, 2};
    int expected4[] = {2, 6, 3, 4, 8, 9, 5};
    int output4[7];
    sort_third(input4, 7, output4);
    assert(arrays_equal(output4, expected4, 7));

    /* Test 5 */
    int input5[] = {5, 8, 3, 4, 6, 9, 2};
    int expected5[] = {2, 8, 3, 4, 6, 9, 5};
    int output5[7];
    sort_third(input5, 7, output5);
    assert(arrays_equal(output5, expected5, 7));

    /* Test 6 */
    int input6[] = {5, 6, 9, 4, 8, 3, 2};
    int expected6[] = {2, 6, 9, 4, 8, 3, 5};
    int output6[7];
    sort_third(input6, 7, output6);
    assert(arrays_equal(output6, expected6, 7));

    /* Test 7 */
    int input7[] = {5, 6, 3, 4, 8, 9, 2, 1};
    int expected7[] = {2, 6, 3, 4, 8, 9, 5, 1};
    int output7[8];
    sort_third(input7, 8, output7);
    assert(arrays_equal(output7, expected7, 8));
}

int main(void) {
    test_sort_third();
    return 0;
}