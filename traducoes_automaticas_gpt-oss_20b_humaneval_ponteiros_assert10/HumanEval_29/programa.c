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
    char strings[20][256];
    int count;
} FilterResult;

void filter_by_prefix(const char **strings, int n_strings, const char *prefix, FilterResult *out) {
    int prefix_len = 0;
    while (prefix[prefix_len] != '\0') {
        prefix_len++;
    }
    out->count = 0;
    for (int i = 0; i < n_strings; ++i) {
        int j = 0;
        while (j < prefix_len && strings[i][j] == prefix[j]) {
            j++;
        }
        if (j == prefix_len) {
            // string matches prefix
            // copy string into output
            int k = 0;
            while (strings[i][k] != '\0' && k < 255) {
                out->strings[out->count][k] = strings[i][k];
                k++;
            }
            out->strings[out->count][k] = '\0';
            out->count++;
            if (out->count >= 20) {
                break; // prevent overflow of fixed-size array
            }
        }
    }
}

/* Test functions */
void check(void) {
    FilterResult res;

    /* Test 1: empty input */
    filter_by_prefix(NULL, 0, "john", &res);
    assert(res.count == 0);

    /* Test 2: normal prefix filtering */
    const char *input[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    int n = 6;
    filter_by_prefix(input, n, "xxx", &res);
    assert(res.count == 3);
    assert(strcmp(res.strings[0], "xxx") == 0);
    assert(strcmp(res.strings[1], "xxxAAA") == 0);
    assert(strcmp(res.strings[2], "xxx") == 0);
}

/* Main entry point */
int main(void) {
    check();
    return 0;
}