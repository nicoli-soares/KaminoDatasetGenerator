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
    char *data;
} string_container;

// Helper function to check if a string is a palindrome
static bool is_palindrome(const char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; ++i) {
        if (s[i] != s[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// Main function: returns a newly allocated palindrome string
char *make_palindrome(const char *string) {
    if (string == NULL || *string == '\0') {
        char *empty = (char *)malloc(1);
        if (!empty) return NULL;
        empty[0] = '\0';
        return empty;
    }

    size_t orig_len = strlen(string);
    size_t beginning_of_suffix = 0;

    // Find the longest suffix that is a palindrome
    while (!is_palindrome(string + beginning_of_suffix)) {
        ++beginning_of_suffix;
    }

    // Build the result: original string + reverse of the prefix
    size_t prefix_len = beginning_of_suffix;
    size_t result_len = orig_len + prefix_len;
    char *result = (char *)malloc(result_len + 1); // +1 for null terminator
    if (!result) return NULL;

    // Copy original string
    memcpy(result, string, orig_len);

    // Copy reversed prefix
    for (size_t i = 0; i < prefix_len; ++i) {
        result[orig_len + i] = string[prefix_len - 1 - i];
    }
    result[result_len] = '\0';

    return result;
}

// Test harness
static void check(char *(*candidate)(const char *)) {
    char *res;

    res = candidate("");
    assert(strcmp(res, "") == 0);
    free(res);

    res = candidate("x");
    assert(strcmp(res, "x") == 0);
    free(res);

    res = candidate("xyz");
    assert(strcmp(res, "xyzyx") == 0);
    free(res);

    res = candidate("xyx");
    assert(strcmp(res, "xyx") == 0);
    free(res);

    res = candidate("jerry");
    assert(strcmp(res, "jerryrrej") == 0);
    free(res);
}

int main(void) {
    check(make_palindrome);
    return 0;
}