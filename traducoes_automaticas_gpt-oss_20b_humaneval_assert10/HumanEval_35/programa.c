#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef int (*candidate_func)(const int*, size_t);

int max_element(const int *l, size_t n) {
    if (n == 0) return 0; /* undefined for empty list; return 0 as safe fallback */
    int m = l[0];
    for (size_t i = 1; i < n; ++i) {
        if (l[i] > m) m = l[i];
    }
    return m;
}

/* ---------- Testes ---------- */

void test_max_element_1() {
    int arr[3] = {1, 2, 3};
    assert(max_element(arr, 3) == 3);
}

void test_max_element_2() {
    int arr[11] = {5, 3, -5, 2, -3, 3, 9, 0, 124, 1, -10};
    assert(max_element(arr, 11) == 124);
}

void run_tests() {
    test_max_element_1();
    test_max_element_2();
}

/* ---------- Main ---------- */

int main() {
    run_tests();
    return 0;
}