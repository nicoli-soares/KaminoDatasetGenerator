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
    int key;
    int value;
} CountEntry_c;

int remove_duplicates(const int *numbers, size_t len, int **out, size_t *out_len) {
    if (!out || !out_len) return -1; // invalid parameters
    if (len == 0) {
        *out = NULL;
        *out_len = 0;
        return 0;
    }

    CountEntry_c *counts = NULL;
    size_t counts_size = 0;

    for (size_t i = 0; i < len; ++i) {
        int n = numbers[i];
        int found = 0;
        for (size_t j = 0; j < counts_size; ++j) {
            if (counts[j].key == n) {
                counts[j].value += 1;
                found = 1;
                break;
            }
        }
        if (!found) {
            CountEntry_c *tmp = realloc(counts, (counts_size + 1) * sizeof(CountEntry_c));
            if (!tmp) { free(counts); return -1; }
            counts = tmp;
            counts[counts_size].key = n;
            counts[counts_size].value = 1;
            counts_size++;
        }
    }

    int *res = malloc(len * sizeof(int));
    if (!res) { free(counts); return -1; }
    size_t res_index = 0;

    for (size_t i = 0; i < len; ++i) {
        int n = numbers[i];
        for (size_t j = 0; j < counts_size; ++j) {
            if (counts[j].key == n) {
                if (counts[j].value <= 1) {
                    res[res_index++] = n;
                }
                break;
            }
        }
    }

    free(counts);
    *out = res;
    *out_len = res_index;
    return 0;
}

void assert_array_equals(const int *expected, size_t expected_len, const int *actual, size_t actual_len) {
    assert(expected_len == actual_len);
    for (size_t i = 0; i < expected_len; ++i) {
        assert(expected[i] == actual[i]);
    }
}

void test_empty() {
    int *result = NULL;
    size_t len = 0;
    int status = remove_duplicates(NULL, 0, &result, &len);
    assert(status == 0);
    assert(len == 0);
    free(result);
}

void test_all_unique() {
    int input[] = {1, 2, 3, 4};
    size_t input_len = 4;
    int *result = NULL;
    size_t len = 0;
    int status = remove_duplicates(input, input_len, &result, &len);
    assert(status == 0);
    int expected[] = {1, 2, 3, 4};
    assert_array_equals(expected, 4, result, len);
    free(result);
}

void test_some_duplicates() {
    int input[] = {1, 2, 3, 2, 4, 3, 5};
    size_t input_len = 7;
    int *result = NULL;
    size_t len = 0;
    int status = remove_duplicates(input, input_len, &result, &len);
    assert(status == 0);
    int expected[] = {1, 4, 5};
    assert_array_equals(expected, 3, result, len);
    free(result);
}

int main(void) {
    test_empty();
    test_all_unique();
    test_some_duplicates();
    return 0;
}