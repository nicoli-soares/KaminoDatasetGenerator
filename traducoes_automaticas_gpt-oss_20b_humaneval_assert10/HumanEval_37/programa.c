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
static int cmp_int(const void *a, const void *b)
{
    int ai = *(const int *)a;
    int bi = *(const int *)b;
    return (ai > bi) - (ai < bi);
}

/* Main function to translate: sort_even */
int* sort_even(const int *arr, size_t n, size_t *out_len)
{
    /* Allocate arrays for even and odd indices */
    size_t e_len = (n + 1) / 2;    /* ceil(n/2) */
    size_t o_len = n / 2;          /* floor(n/2) */

    int *evens = (int *)malloc(e_len * sizeof(int));
    int *odds  = (int *)malloc(o_len  * sizeof(int));
    if (!evens || !odds) {
        /* In case of allocation failure, return NULL */
        free(evens);
        free(odds);
        *out_len = 0;
        return NULL;
    }

    /* Split original array into evens and odds */
    size_t i, j, k;
    for (i = 0, j = 0, k = 0; i < n; ++i) {
        if ((i & 1) == 0) {          /* even index */
            evens[j++] = arr[i];
        } else {                     /* odd index */
            odds[k++] = arr[i];
        }
    }

    /* Sort the evens array */
    qsort(evens, e_len, sizeof(int), cmp_int);

    /* Prepare result array */
    int *ans = (int *)malloc(n * sizeof(int));
    if (!ans) {
        free(evens);
        free(odds);
        *out_len = 0;
        return NULL;
    }

    /* Merge sorted evens with odds */
    size_t min_len = (o_len < e_len) ? o_len : e_len;
    for (i = 0; i < min_len; ++i) {
        ans[2 * i]     = evens[i];
        ans[2 * i + 1] = odds[i];
    }
    if (e_len > o_len) {
        ans[2 * min_len] = evens[min_len];
    }

    /* Clean up */
    free(evens);
    free(odds);

    *out_len = n;
    return ans;
}

/* Test functions */
void test_sort_even(void)
{
    size_t out_len;
    int *res;

    /* Test 1 */
    int arr1[] = {1, 2, 3};
    res = sort_even(arr1, 3, &out_len);
    assert(out_len == 3);
    assert(res[0] == 1 && res[1] == 2 && res[2] == 3);
    free(res);

    /* Test 2 */
    int arr2[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int expected2[] = {-10, 3, -5, 2, -3, 3, 5, 0, 9, 1, 123};
    res = sort_even(arr2, 11, &out_len);
    assert(out_len == 11);
    for (size_t i = 0; i < 11; ++i) {
        assert(res[i] == expected2[i]);
    }
    free(res);

    /* Test 3 */
    int arr3[] = {5, 8, -12, 4, 23, 2, 3, 11, 12, -10};
    int expected3[] = {-12, 8, 3, 4, 5, 2, 12, 11, 23, -10};
    res = sort_even(arr3, 10, &out_len);
    assert(out_len == 10);
    for (size_t i = 0; i < 10; ++i) {
        assert(res[i] == expected3[i]);
    }
    free(res);
}

/* Main entry point */
int main(void)
{
    test_sort_even();
    return 0;
}