#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define MAX_PREFIXES 256
#define MAX_PREFIX_LEN 256

/* --- Utility functions --------------------------------------------------- */

/* Compute the length of a C-string (null-terminated) */
static int my_strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

/* Compare two C-strings. Returns 0 if equal. */
static int my_strcmp(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return a[i] - b[i];
        }
        i++;
    }
    return (a[i] == b[i]) ? 0 : (a[i] == '\0' ? -1 : 1);
}

/* --- Core function ------------------------------------------------------- */

/*
 * all_prefixes: generate all prefixes of the input string, from shortest
 * to longest. The prefixes are written into the result array, which must
 * have enough space to hold at least strlen(string)+1 prefixes, each
 * with room for MAX_PREFIX_LEN characters.
 *
 * Parameters:
 *   string: input null-terminated string
 *   result: 2D array to receive prefixes
 *   count: pointer to int where the number of prefixes will be stored
 *
 * Return: void (count is set)
 */
void all_prefixes(const char *string, char result[][MAX_PREFIX_LEN], int *count) {
    int n = my_strlen(string);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        /* Copy characters up to i (inclusive) */
        for (int j = 0; j <= i; j++) {
            result[idx][j] = string[j];
        }
        result[idx][i + 1] = '\0';  /* null-terminate */
        idx++;
    }
    *count = idx;
}

/* --- Tests --------------------------------------------------------------- */

static void test_empty(void) {
    char prefixes[MAX_PREFIXES][MAX_PREFIX_LEN];
    int count;
    all_prefixes("", prefixes, &count);
    assert(count == 0);
}

static void test_regular(void) {
    char prefixes[MAX_PREFIXES][MAX_PREFIX_LEN];
    int count;
    all_prefixes("asdfgh", prefixes, &count);
    assert(count == 6);
    const char *expected[] = {"a", "as", "asd", "asdf", "asdfg", "asdfgh"};
    for (int i = 0; i < count; i++) {
        assert(my_strcmp(prefixes[i], expected[i]) == 0);
    }
}

static void test_WWW(void) {
    char prefixes[MAX_PREFIXES][MAX_PREFIX_LEN];
    int count;
    all_prefixes("WWW", prefixes, &count);
    assert(count == 3);
    const char *expected[] = {"W", "WW", "WWW"};
    for (int i = 0; i < count; i++) {
        assert(my_strcmp(prefixes[i], expected[i]) == 0);
    }
}

/* Main: execute all tests */
int main(void) {
    test_empty();
    test_regular();
    test_WWW();
    return 0;
}