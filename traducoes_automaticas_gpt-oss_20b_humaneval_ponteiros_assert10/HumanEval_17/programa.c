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
    int beats[256];
    int count;
} ParseResult;

/* Convert a music string into an array of beat counts.
   The result is written into the provided buffer 'beats',
   and the number of elements is stored in '*count'.
   Returns 0 on success. */
int parse_music_c(const char *music_string, int *beats, int *count) {
    int idx = 0;
    const char *p = music_string;
    while (*p) {
        /* Skip leading spaces */
        while (*p == ' ') {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        /* Find end of the token */
        const char *start = p;
        while (*p && *p != ' ') {
            p++;
        }
        int len = p - start;
        if (len == 0) {
            continue;
        }
        /* Copy token into a temporary buffer */
        char token[4] = {0};
        if (len < 4) {
            for (int i = 0; i < len; i++) {
                token[i] = start[i];
            }
        }
        /* Map token to beat value */
        if (len == 1 && token[0] == 'o') {
            beats[idx++] = 4;
        } else if (len == 2 && token[0] == 'o' && token[1] == '|') {
            beats[idx++] = 2;
        } else if (len == 2 && token[0] == '.' && token[1] == '|') {
            beats[idx++] = 1;
        } else {
            /* Unknown token – ignore (Python would also ignore it) */
        }
    }
    *count = idx;
    return 0;
}

/* Helper to compare two integer arrays of length n */
void assert_array(const int *actual, const int *expected, int n) {
    for (int i = 0; i < n; i++) {
        assert(actual[i] == expected[i]);
    }
}

/* Test cases */

void test_empty() {
    int beats[256];
    int count;
    parse_music_c("", beats, &count);
    assert(count == 0);
}

void test_whole() {
    int beats[256];
    int count;
    parse_music_c("o o o o", beats, &count);
    assert(count == 4);
    int expected[] = {4, 4, 4, 4};
    assert_array(beats, expected, 4);
}

void test_quarter() {
    int beats[256];
    int count;
    parse_music_c(".| .| .| .|", beats, &count);
    assert(count == 4);
    int expected[] = {1, 1, 1, 1};
    assert_array(beats, expected, 4);
}

void test_mix1() {
    int beats[256];
    int count;
    parse_music_c("o| o| .| .| o o o o", beats, &count);
    assert(count == 8);
    int expected[] = {2, 2, 1, 1, 4, 4, 4, 4};
    assert_array(beats, expected, 8);
}

void test_mix2() {
    int beats[256];
    int count;
    parse_music_c("o| .| o| .| o o| o o|", beats, &count);
    assert(count == 8);
    int expected[] = {2, 1, 2, 1, 4, 2, 4, 2};
    assert_array(beats, expected, 8);
}

int main(void) {
    test_empty();
    test_whole();
    test_quarter();
    test_mix1();
    test_mix2();
    return 0;
}