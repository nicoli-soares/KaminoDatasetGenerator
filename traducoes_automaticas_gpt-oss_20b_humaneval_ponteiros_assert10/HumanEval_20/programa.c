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
    double first;
    double second;
} Pair;

Pair find_closest_elements(const double *numbers, size_t n) {
    Pair result = {0.0, 0.0};
    double min_distance = -1.0;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == j) continue;

            double dist = fabs(numbers[i] - numbers[j]);

            if (min_distance < 0 || dist < min_distance) {
                min_distance = dist;
                if (numbers[i] <= numbers[j]) {
                    result.first = numbers[i];
                    result.second = numbers[j];
                } else {
                    result.first = numbers[j];
                    result.second = numbers[i];
                }
            }
        }
    }
    return result;
}

static inline bool pair_equals(Pair a, Pair b) {
    return (fabs(a.first - b.first) < 1e-6) && (fabs(a.second - b.second) < 1e-6);
}

void test_find_closest_elements() {
    double arr1[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    Pair r1 = find_closest_elements(arr1, sizeof(arr1)/sizeof(arr1[0]));
    assert(pair_equals(r1, (Pair){3.9, 4.0}));

    double arr2[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    Pair r2 = find_closest_elements(arr2, sizeof(arr2)/sizeof(arr2[0]));
    assert(pair_equals(r2, (Pair){5.0, 5.9}));

    double arr3[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.2};
    Pair r3 = find_closest_elements(arr3, sizeof(arr3)/sizeof(arr3[0]));
    assert(pair_equals(r3, (Pair){2.0, 2.2}));

    double arr4[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    Pair r4 = find_closest_elements(arr4, sizeof(arr4)/sizeof(arr4[0]));
    assert(pair_equals(r4, (Pair){2.0, 2.0}));

    double arr5[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    Pair r5 = find_closest_elements(arr5, sizeof(arr5)/sizeof(arr5[0]));
    assert(pair_equals(r5, (Pair){2.2, 3.1}));
}

int main(void) {
    test_find_closest_elements();
    return 0;
}