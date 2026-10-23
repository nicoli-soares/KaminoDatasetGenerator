#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

char *string_sequence(int n) {
    if (n < 0) {
        return NULL;
    }

    /* Calculate the maximum number of digits of n */
    int max_digits = 1;
    int temp = n;
    while (temp >= 10) {
        temp /= 10;
        max_digits++;
    }

    /* Estimate buffer size: each number up to max_digits chars,
       plus one space between numbers, plus null terminator */
    int total_len = max_digits * (n + 1) + n + 1;
    char *result = malloc(total_len);
    if (!result) {
        return NULL;
    }

    int pos = 0;
    for (int i = 0; i <= n; i++) {
        int written = sprintf(result + pos, "%d", i);
        pos += written;
        if (i < n) {
            result[pos++] = ' ';
        }
    }
    result[pos] = '\0';
    return result;
}

/* ---------- Test functions ---------- */
void test_string_sequence() {
    char *res;

    /* Test 1 */
    res = string_sequence(0);
    assert(res != NULL);
    assert(strcmp(res, "0") == 0);
    free(res);

    /* Test 2 */
    res = string_sequence(3);
    assert(res != NULL);
    assert(strcmp(res, "0 1 2 3") == 0);
    free(res);

    /* Test 3 */
    res = string_sequence(10);
    assert(res != NULL);
    assert(strcmp(res, "0 1 2 3 4 5 6 7 8 9 10") == 0);
    free(res);
}

/* ---------- Main ---------- */
int main(void) {
    test_string_sequence();
    return 0;
}