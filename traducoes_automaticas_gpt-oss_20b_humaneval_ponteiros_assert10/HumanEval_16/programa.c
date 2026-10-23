#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef int (*count_func)(const char *);

int count_distinct_characters(const char *string) {
    bool seen[256] = {false};
    int count = 0;
    for (const char *p = string; *p != '\0'; ++p) {
        unsigned char ch = (unsigned char)tolower((unsigned char)*p);
        if (!seen[ch]) {
            seen[ch] = true;
            ++count;
        }
    }
    return count;
}

void check(count_func candidate) {
    assert(candidate("") == 0);
    assert(candidate("abcde") == 5);
    assert(candidate("abcde" "cade" "CADE") == 5);
    assert(candidate("aaaaAAAAaaaa") == 1);
    assert(candidate("Jerry jERRY JeRRRY") == 5);
}

int main(void) {
    check(count_distinct_characters);
    return 0;
}