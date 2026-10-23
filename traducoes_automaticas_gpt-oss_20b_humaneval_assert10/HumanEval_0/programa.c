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
    const double *numbers;
    size_t n;
    double threshold;
} HasCloseParams;

bool has_close_elements(const double *numbers, size_t n, double threshold) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                double diff = numbers[i] - numbers[j];
                if (diff < 0) diff = -diff; // absolute value
                if (diff < threshold) {
                    return true;
                }
            }
        }
    }
    return false;
}

/* Test function equivalent to the Python check() */
void check(void) {
    /* 1 */
    double arr1[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    size_t n1 = sizeof(arr1)/sizeof(arr1[0]);
    assert(has_close_elements(arr1, n1, 0.3) == true);
    assert(has_close_elements(arr1, n1, 0.05) == false);

    /* 2 */
    double arr2[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    size_t n2 = sizeof(arr2)/sizeof(arr2[0]);
    assert(has_close_elements(arr2, n2, 0.95) == true);
    assert(has_close_elements(arr2, n2, 0.8) == false);

    /* 3 */
    double arr3[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    size_t n3 = sizeof(arr3)/sizeof(arr3[0]);
    assert(has_close_elements(arr3, n3, 0.1) == true);

    /* 4 */
    double arr4[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    size_t n4 = sizeof(arr4)/sizeof(arr4[0]);
    assert(has_close_elements(arr4, n4, 1.0) == true);
    assert(has_close_elements(arr4, n4, 0.5) == false);
}

int main(void) {
    check();
    return 0;
}