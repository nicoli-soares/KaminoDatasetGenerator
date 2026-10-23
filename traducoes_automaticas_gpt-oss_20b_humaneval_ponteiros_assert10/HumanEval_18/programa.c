#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int how_many_times(const char *string, const char *substring) {
    if (string == NULL || substring == NULL) return 0;
    int len_string = strlen(string);
    int len_sub = strlen(substring);
    int times = 0;
    if (len_sub == 0) {
        // Python semantics: empty substring matches at every position, including after the last character
        return len_string + 1;
    }
    for (int i = 0; i <= len_string - len_sub; ++i) {
        if (strncmp(string + i, substring, len_sub) == 0) {
            ++times;
        }
    }
    return times;
}

void run_tests(void) {
    // Test 1: substring not found
    assert(how_many_times("", "x") == 0);
    // Test 2: single-character substring with overlaps
    assert(how_many_times("xyxyxyx", "x") == 4);
    // Test 3: longer substring with overlaps
    assert(how_many_times("cacacacac", "cac") == 4);
    // Test 4: standard substring match
    assert(how_many_times("john doe", "john") == 1);
}

int main(void) {
    run_tests();
    return 0;
}