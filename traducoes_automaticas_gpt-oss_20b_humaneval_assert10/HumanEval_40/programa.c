#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

bool triples_sum_to_zero(int *l, int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            for (int k = j + 1; k < len; ++k) {
                if (l[i] + l[j] + l[k] == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main(void) {
    /* Test 1 */
    int arr1[] = {1, 3, 5, 0};
    assert(triples_sum_to_zero(arr1, 4) == false);

    /* Test 2 */
    int arr2[] = {1, 3, 5, -1};
    assert(triples_sum_to_zero(arr2, 4) == false);

    /* Test 3 */
    int arr3[] = {1, 3, -2, 1};
    assert(triples_sum_to_zero(arr3, 4) == true);

    /* Test 4 */
    int arr4[] = {1, 2, 3, 7};
    assert(triples_sum_to_zero(arr4, 4) == false);

    /* Test 5 */
    int arr5[] = {1, 2, 5, 7};
    assert(triples_sum_to_zero(arr5, 4) == false);

    /* Test 6 */
    int arr6[] = {2, 4, -5, 3, 9, 7};
    assert(triples_sum_to_zero(arr6, 6) == true);

    /* Test 7 */
    int arr7[] = {1};
    assert(triples_sum_to_zero(arr7, 1) == false);

    /* Test 8 */
    int arr8[] = {1, 3, 5, -100};
    assert(triples_sum_to_zero(arr8, 4) == false);

    /* Test 9 */
    int arr9[] = {100, 3, 5, -100};
    assert(triples_sum_to_zero(arr9, 4) == false);

    return 0;
}