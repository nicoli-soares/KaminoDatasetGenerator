#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define MAX_STRING_LEN 256
#define MAX_RESULT 10

/* Helper to check if 'substr' occurs in 'str' */
int contains_substring(const char *str, const char *substr) {
    if (!*substr) return 1; /* empty substring matches everything */
    for (int i = 0; str[i] != '\0'; i++) {
        int j = 0;
        while (str[i + j] != '\0' && substr[j] != '\0' && str[i + j] == substr[j]) {
            j++;
        }
        if (substr[j] == '\0') return 1;
    }
    return 0;
}

/* Main function: filters strings that contain the given substring.
   It writes the matched strings into 'result' and updates 'n_result'.
   Returns 0 on success. */
int filter_by_substring(const char *strings[], int n_strings,
                       const char *substring,
                       char result[][MAX_STRING_LEN], int *n_result) {
    *n_result = 0;
    for (int i = 0; i < n_strings; i++) {
        if (contains_substring(strings[i], substring)) {
            /* copy the string into the result buffer */
            const char *src = strings[i];
            char *dst = result[*n_result];
            int j = 0;
            while (src[j] != '\0' && j < MAX_STRING_LEN - 1) {
                dst[j] = src[j];
                j++;
            }
            dst[j] = '\0';
            (*n_result)++;
        }
    }
    return 0;
}

/* Helper to compare two arrays of strings.
   Returns 1 if they are equal (same length and all elements match). */
int compare_string_arrays(const char res[][MAX_STRING_LEN], int n1,
                          const char *arr2[], int n2) {
    if (n1 != n2) return 0;
    for (int i = 0; i < n1; i++) {
        if (strcmp(res[i], arr2[i]) != 0) return 0;
    }
    return 1;
}

/* Test cases for filter_by_substring */
void test_filter_by_substring(void) {
    /* Test 1: empty input */
    const char **input1 = NULL;
    int n1 = 0;
    char result1[MAX_RESULT][MAX_STRING_LEN];
    int n_result1;
    int status = filter_by_substring(input1, n1, "john", result1, &n_result1);
    assert(status == 0);
    assert(n_result1 == 0);

    /* Test 2 */
    const char *input2[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    int n2 = 6;
    const char *expected2[] = {"xxx", "xxxAAA", "xxx"};
    int n_expected2 = 3;
    char result2[MAX_RESULT][MAX_STRING_LEN];
    int n_result2;
    status = filter_by_substring(input2, n2, "xxx", result2, &n_result2);
    assert(status == 0);
    assert(n_result2 == n_expected2);
    assert(compare_string_arrays(result2, n_result2, expected2, n_expected2));

    /* Test 3 */
    const char *input3[] = {"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"};
    int n3 = 6;
    const char *expected3[] = {"xxx", "aaaxxy", "xxxAAA", "xxx"};
    int n_expected3 = 4;
    char result3[MAX_RESULT][MAX_STRING_LEN];
    int n_result3;
    status = filter_by_substring(input3, n3, "xx", result3, &n_result3);
    assert(status == 0);
    assert(n_result3 == n_expected3);
    assert(compare_string_arrays(result3, n_result3, expected3, n_expected3));

    /* Test 4 */
    const char *input4[] = {"grunt", "trumpet", "prune", "gruesome"};
    int n4 = 4;
    const char *expected4[] = {"grunt", "prune"};
    int n_expected4 = 2;
    char result4[MAX_RESULT][MAX_STRING_LEN];
    int n_result4;
    status = filter_by_substring(input4, n4, "run", result4, &n_result4);
    assert(status == 0);
    assert(n_result4 == n_expected4);
    assert(compare_string_arrays(result4, n_result4, expected4, n_expected4));
}

int main(void) {
    test_filter_by_substring();
    return 0;
}