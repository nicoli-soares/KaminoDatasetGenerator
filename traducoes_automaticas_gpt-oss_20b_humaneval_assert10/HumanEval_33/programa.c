#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Struct and helper definitions */
typedef struct {
    int key;
    int value;
} keyvalue_t;

int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

bool arrays_equal(const int *a, const int *b, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/* Core function: sort elements at indices divisible by three */
int* sort_third(const int *arr, size_t n) {
    if (!arr) return NULL;
    int *res = malloc(n * sizeof(int));
    if (!res) return NULL;
    memcpy(res, arr, n * sizeof(int));

    /* Collect values at indices divisible by 3 */
    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i % 3 == 0) count++;
    }
    int *vals = malloc(count * sizeof(int));
    if (!vals) { free(res); return NULL; }
    size_t idx = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i % 3 == 0) {
            vals[idx++] = res[i];
        }
    }

    /* Sort the collected values */
    qsort(vals, count, sizeof(int), cmp_int);

    /* Place sorted values back into the result array */
    idx = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i % 3 == 0) {
            res[i] = vals[idx++];
        }
    }

    free(vals);
    return res;
}

/* Test cases derived from the original Python tests */
void test1(void) {
    int input[] = {1, 2, 3};
    size_t n = 3;
    int *out = sort_third(input, n);
    int expected[] = {1, 2, 3};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

void test2(void) {
    int input[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    size_t n = 11;
    int *out = sort_third(input, n);
    int expected[] = {1, 3, -5, 2, -3, 3, 5, 0, 123, 9, -10};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

void test3(void) {
    int input[] = {5, 8, -12, 4, 23, 2, 3, 11, 12, -10};
    size_t n = 10;
    int *out = sort_third(input, n);
    int expected[] = {-10, 8, -12, 3, 23, 2, 4, 11, 12, 5};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

void test4(void) {
    int input[] = {5, 6, 3, 4, 8, 9, 2};
    size_t n = 7;
    int *out = sort_third(input, n);
    int expected[] = {2, 6, 3, 4, 8, 9, 5};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

void test5(void) {
    int input[] = {5, 8, 3, 4, 6, 9, 2};
    size_t n = 7;
    int *out = sort_third(input, n);
    int expected[] = {2, 8, 3, 4, 6, 9, 5};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

void test6(void) {
    int input[] = {5, 6, 9, 4, 8, 3, 2};
    size_t n = 7;
    int *out = sort_third(input, n);
    int expected[] = {2, 6, 9, 4, 8, 3, 5};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

void test7(void) {
    int input[] = {5, 6, 3, 4, 8, 9, 2, 1};
    size_t n = 8;
    int *out = sort_third(input, n);
    int expected[] = {2, 6, 3, 4, 8, 9, 5, 1};
    assert(out);
    assert(arrays_equal(out, expected, n));
    free(out);
}

/* Main function to run all tests */
int main(void) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    return 0;
}