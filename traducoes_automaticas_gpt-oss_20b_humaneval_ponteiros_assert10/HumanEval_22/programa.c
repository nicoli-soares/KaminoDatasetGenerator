#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_DICT,
    TYPE_LIST,
    TYPE_OTHER
} ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        double d;
        const char *s;
    } value;
} AnyValue;

int filter_integers(const AnyValue *values, int n, int **out_values, int *out_len) {
    int count = 0;
    for (int idx = 0; idx < n; idx++) {
        if (values[idx].type == TYPE_INT) {
            count++;
        }
    }
    *out_len = count;
    if (count == 0) {
        *out_values = NULL;
        return 0;
    }
    *out_values = (int *)malloc(count * sizeof(int));
    if (*out_values == NULL) {
        return -1;
    }
    int pos = 0;
    for (int idx = 0; idx < n; idx++) {
        if (values[idx].type == TYPE_INT) {
            (*out_values)[pos++] = values[idx].value.i;
        }
    }
    return 0;
}

void assert_int_array_equal(const int *actual, int actual_len,
                            const int *expected, int expected_len) {
    assert(actual_len == expected_len);
    for (int i = 0; i < actual_len; i++) {
        assert(actual[i] == expected[i]);
    }
}

typedef int (*filter_func_t)(const AnyValue *, int, int **, int *);

void check(filter_func_t candidate) {
    /* Test 1: empty input */
    const AnyValue *vals1 = NULL;
    int *out1;
    int len1;
    int ret1 = candidate(vals1, 0, &out1, &len1);
    assert(ret1 == 0);
    assert(len1 == 0);
    assert(out1 == NULL);

    /* Test 2: mixed types */
    AnyValue vals2[6] = {
        {TYPE_INT, .value.i = 4},
        {TYPE_DICT, .value.s = NULL},
        {TYPE_LIST, .value.s = NULL},
        {TYPE_FLOAT, .value.d = 23.2},
        {TYPE_INT, .value.i = 9},
        {TYPE_STRING, .value.s = "adasd"}
    };
    int *out2;
    int len2;
    int ret2 = candidate(vals2, 6, &out2, &len2);
    assert(ret2 == 0);
    int expected2[2] = {4, 9};
    assert_int_array_equal(out2, len2, expected2, 2);
    free(out2);

    /* Test 3: repeated integers */
    AnyValue vals3[6] = {
        {TYPE_INT, .value.i = 3},
        {TYPE_STRING, .value.s = "c"},
        {TYPE_INT, .value.i = 3},
        {TYPE_INT, .value.i = 3},
        {TYPE_STRING, .value.s = "a"},
        {TYPE_STRING, .value.s = "b"}
    };
    int *out3;
    int len3;
    int ret3 = candidate(vals3, 6, &out3, &len3);
    assert(ret3 == 0);
    int expected3[3] = {3, 3, 3};
    assert_int_array_equal(out3, len3, expected3, 3);
    free(out3);
}

int main(void) {
    check(filter_integers);
    return 0;
}