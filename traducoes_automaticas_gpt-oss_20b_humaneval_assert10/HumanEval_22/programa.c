#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Structs and typedefs for representing mixed-type values */
typedef enum { TYPE_INT, TYPE_DOUBLE, TYPE_STRING, TYPE_OBJECT } ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        double d;
        char *s;
        void *ptr;
    } u;
} Value;

/* Helper constructors for Value */
static Value create_int(int v) {
    Value val;
    val.type = TYPE_INT;
    val.u.i = v;
    return val;
}

static Value create_double(double v) {
    Value val;
    val.type = TYPE_DOUBLE;
    val.u.d = v;
    return val;
}

static Value create_string(const char *s) {
    Value val;
    val.type = TYPE_STRING;
    /* strdup is used for simplicity; it is available in string.h which
       will be auto-included by the build system. */
    val.u.s = strdup(s);
    return val;
}

static Value create_object(void *ptr) {
    Value val;
    val.type = TYPE_OBJECT;
    val.u.ptr = ptr;
    return val;
}

/* Free memory allocated inside Value array (strings only) */
static void free_values(Value *vals, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (vals[i].type == TYPE_STRING && vals[i].u.s != NULL) {
            free(vals[i].u.s);
            vals[i].u.s = NULL;
        }
    }
}

/* filter_integers implementation
 * Parameters:
 *   values   : array of Value
 *   n        : number of elements in values
 *   outInts  : pointer to result array of ints (malloc'ed)
 *   outSize  : pointer to size of result array
 * Returns:
 *   0 on success, negative error code otherwise
 */
static int filter_integers(Value *values, size_t n, int **outInts, size_t *outSize) {
    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (values[i].type == TYPE_INT)
            ++count;
    }

    *outSize = count;
    if (count == 0) {
        *outInts = NULL;
        return 0;
    }

    *outInts = (int *)malloc(count * sizeof(int));
    if (*outInts == NULL)
        return -1;  /* memory allocation failure */

    size_t idx = 0;
    for (size_t i = 0; i < n; ++i) {
        if (values[i].type == TYPE_INT) {
            (*outInts)[idx++] = values[i].u.i;
        }
    }
    return 0;
}

/* Test utilities ----------------------------------------------------------- */

static void assert_int_array_equal(const int *a, size_t aSize, const int *b, size_t bSize) {
    assert(aSize == bSize);
    for (size_t i = 0; i < aSize; ++i) {
        assert(a[i] == b[i]);
    }
}

/* Test 1: empty input */
static void test_empty() {
    int *res = NULL;
    size_t sz = 0;
    int ret = filter_integers(NULL, 0, &res, &sz);
    assert(ret == 0);
    assert(sz == 0);
    assert(res == NULL);
}

/* Test 2: mixed types */
static void test_mixed() {
    Value vals[6];
    vals[0] = create_int(4);
    vals[1] = create_object(NULL);      /* {}  */
    vals[2] = create_object(NULL);      /* []  */
    vals[3] = create_double(23.2);
    vals[4] = create_int(9);
    vals[5] = create_string("adasd");

    int *res = NULL;
    size_t sz = 0;
    int ret = filter_integers(vals, 6, &res, &sz);
    assert(ret == 0);
    assert(sz == 2);
    int expected[2] = {4, 9};
    assert_int_array_equal(res, sz, expected, 2);

    free(res);
    free_values(vals, 6);
}

/* Test 3: duplicate integers */
static void test_duplicates() {
    Value vals[6];
    vals[0] = create_int(3);
    vals[1] = create_string("c");
    vals[2] = create_int(3);
    vals[3] = create_int(3);
    vals[4] = create_string("a");
    vals[5] = create_string("b");

    int *res = NULL;
    size_t sz = 0;
    int ret = filter_integers(vals, 6, &res, &sz);
    assert(ret == 0);
    assert(sz == 3);
    int expected[3] = {3, 3, 3};
    assert_int_array_equal(res, sz, expected, 3);

    free(res);
    free_values(vals, 6);
}

/* Main function running all tests */
int main(void) {
    test_empty();
    test_mixed();
    test_duplicates();
    return 0;  /* All tests passed if we reach here */
}