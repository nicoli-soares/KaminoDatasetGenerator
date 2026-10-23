#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Structs and typedefs for the factorization problem */
typedef int (*factor_func_t)(int, int *, int *);

/* Factorization function */
/* Returns 0 on success, negative on error (not used in tests). */
int factorize(int n, int *result, int *len_out)
{
    int i = 2;
    int len = 0;
    if (n <= 1) {
        *len_out = 0;
        return 0;
    }
    while (i <= (int)(sqrt((double)n) + 1)) {
        if (n % i == 0) {
            result[len++] = i;
            n /= i;
        } else {
            i++;
        }
    }
    if (n > 1) {
        result[len++] = n;
    }
    *len_out = len;
    return 0;
}

/* Helper to compare two integer arrays */
bool arrays_equal(const int *a, const int *b, int len)
{
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/* Test function similar to the original Python check() */
void check(factor_func_t candidate)
{
    int res[20];
    int len;

    /* Test 1 */
    candidate(2, res, &len);
    assert(len == 1 && res[0] == 2);

    /* Test 2 */
    candidate(4, res, &len);
    assert(len == 2 && res[0] == 2 && res[1] == 2);

    /* Test 3 */
    candidate(8, res, &len);
    assert(len == 3 && res[0] == 2 && res[1] == 2 && res[2] == 2);

    /* Test 4 */
    candidate(3 * 19, res, &len);
    assert(len == 2 && res[0] == 3 && res[1] == 19);

    /* Test 5 */
    candidate(3 * 19 * 3 * 19, res, &len);
    assert(len == 4 && res[0] == 3 && res[1] == 3 && res[2] == 19 && res[3] == 19);

    /* Test 6 */
    candidate(3 * 19 * 3 * 19 * 3 * 19, res, &len);
    assert(len == 6 &&
           res[0] == 3 && res[1] == 3 && res[2] == 3 &&
           res[3] == 19 && res[4] == 19 && res[5] == 19);

    /* Test 7 */
    candidate(3 * 19 * 19 * 19, res, &len);
    assert(len == 4 &&
           res[0] == 3 && res[1] == 19 && res[2] == 19 && res[3] == 19);

    /* Test 8 */
    candidate(3 * 2 * 3, res, &len);
    assert(len == 3 &&
           res[0] == 2 && res[1] == 3 && res[2] == 3);
}

/* Main function to run all tests */
int main(void)
{
    check(factorize);
    return 0;
}