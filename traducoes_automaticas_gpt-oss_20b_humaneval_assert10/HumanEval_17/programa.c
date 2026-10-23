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
    const char *key;
    int value;
} NoteMapEntry;

int map_token(const char *start, int len, int *value) {
    if (len == 1 && start[0] == 'o') {
        *value = 4;
        return 1;
    }
    if (len == 2 && start[0] == 'o' && start[1] == '|') {
        *value = 2;
        return 1;
    }
    if (len == 2 && start[0] == '.' && start[1] == '|') {
        *value = 1;
        return 1;
    }
    return 0;
}

/* 
 * parse_music_c: parses a music string and fills the output array with beat counts.
 * Parameters:
 *   music_string: input C string
 *   out: pre‑allocated array of at least 256 ints
 *   out_len: pointer to an int where the number of parsed notes will be stored
 * Returns:
 *   0 on success
 */
int parse_music_c(const char *music_string, int *out, int *out_len) {
    const char *p = music_string;
    int idx = 0;
    while (*p) {
        /* skip any leading spaces */
        while (*p == ' ') p++;
        if (*p == 0) break;

        const char *start = p;
        while (*p != ' ' && *p != 0) p++;
        int len = p - start;

        int val = 0;
        if (map_token(start, len, &val)) {
            out[idx++] = val;
        }
    }
    *out_len = idx;
    return 0;
}

/* Helper to compare two integer arrays */
void assert_array_equals(int *actual, int actual_len, int *expected, int expected_len) {
    assert(actual_len == expected_len);
    for (int i = 0; i < expected_len; ++i) {
        assert(actual[i] == expected[i]);
    }
}

/* Test cases corresponding to the original Python tests */

void test_empty() {
    int out[256];
    int len;
    parse_music_c("", out, &len);
    assert(len == 0);
}

void test_o() {
    int out[256];
    int len;
    parse_music_c("o o o o", out, &len);
    int expected[4] = {4, 4, 4, 4};
    assert_array_equals(out, len, expected, 4);
}

void test_quarter() {
    int out[256];
    int len;
    parse_music_c(".| .| .| .|", out, &len);
    int expected[4] = {1, 1, 1, 1};
    assert_array_equals(out, len, expected, 4);
}

void test_mix1() {
    int out[256];
    int len;
    parse_music_c("o| o| .| .| o o o o", out, &len);
    int expected[8] = {2, 2, 1, 1, 4, 4, 4, 4};
    assert_array_equals(out, len, expected, 8);
}

void test_mix2() {
    int out[256];
    int len;
    parse_music_c("o| .| o| .| o o| o o|", out, &len);
    int expected[8] = {2, 1, 2, 1, 4, 2, 4, 2};
    assert_array_equals(out, len, expected, 8);
}

int main(void) {
    test_empty();
    test_o();
    test_quarter();
    test_mix1();
    test_mix2();
    return 0;
}