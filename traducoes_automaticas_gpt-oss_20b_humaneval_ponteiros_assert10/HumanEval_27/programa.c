#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// C translation of the Python function flip_case
// The function returns a newly allocated string with cases swapped.
// The caller is responsible for freeing the returned string.

char* flip_case_c(const char* string) {
    // Calculate the length of the input string
    size_t len = 0;
    while (string[len] != '\0') {
        ++len;
    }

    // Allocate memory for the result (+1 for the null terminator)
    char* out = (char*)malloc(len + 1);
    if (!out) {
        return NULL; // allocation failed
    }

    // Swap the case of each character
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = string[i];
        if (c >= 'a' && c <= 'z') {
            out[i] = c - 'a' + 'A'; // lowercase → uppercase
        } else if (c >= 'A' && c <= 'Z') {
            out[i] = c - 'A' + 'a'; // uppercase → lowercase
        } else {
            out[i] = c; // non‑alphabetic characters unchanged
        }
    }
    out[len] = '\0'; // null‑terminate the result
    return out;
}

// ---------- Test functions ----------
void test_flip_case(void) {
    char* res;

    // Test 1: empty string
    res = flip_case_c("");
    assert(res != NULL);
    assert(strcmp(res, "") == 0);
    free(res);

    // Test 2: simple mixed case with punctuation
    res = flip_case_c("Hello!");
    assert(res != NULL);
    assert(strcmp(res, "hELLO!") == 0);
    free(res);

    // Test 3: longer sentence
    res = flip_case_c("These violent delights have violent ends");
    assert(res != NULL);
    assert(strcmp(res, "tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS") == 0);
    free(res);
}

// ---------- Main ----------
int main(void) {
    test_flip_case();
    return 0;
}