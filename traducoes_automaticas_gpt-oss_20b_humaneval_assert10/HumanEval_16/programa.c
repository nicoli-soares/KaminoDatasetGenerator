#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef unsigned char uchar;

int count_distinct_characters(const char *string) {
    bool seen[256] = {false};
    int count = 0;
    for (const char *p = string; *p; ++p) {
        uchar c = (uchar)*p;
        /* Convert to lowercase for ASCII letters */
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        if (!seen[c]) {
            seen[c] = true;
            count++;
        }
    }
    return count;
}

/* Test function */
void test_count_distinct_characters() {
    /* Test case: empty string */
    assert(count_distinct_characters("") == 0);
    /* Test case: unique lowercase letters */
    assert(count_distinct_characters("abcde") == 5);
    /* Test case: mix of lowercase and uppercase, repeated letters */
    assert(count_distinct_characters("abcde" "cade" "CADE") == 5);
    /* Test case: all same letter with different cases */
    assert(count_distinct_characters("aaaaAAAAaaaa") == 1);
    /* Test case: string with spaces and repeated words */
    assert(count_distinct_characters("Jerry jERRY JeRRRY") == 5);
}

int main(void) {
    test_count_distinct_characters();
    return 0;
}