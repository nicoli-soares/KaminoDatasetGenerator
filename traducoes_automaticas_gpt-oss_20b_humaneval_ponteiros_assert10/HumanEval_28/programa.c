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
    size_t value;
} StringLength;

// Concatenate an array of strings into a single string.
// `strings`: array of pointers to C-strings.
// `n`: number of strings in the array.
// `out`: buffer where the result will be written.
// `out_size`: size of the buffer `out` in bytes.
// Returns 0 on success, -1 if the buffer is too small.
int concatenate(const char *strings[], int n, char *out, size_t out_size) {
    size_t total_len = 0;
    for (int i = 0; i < n; i++) {
        total_len += strlen(strings[i]);
    }
    // Include space for the terminating null character.
    if (total_len + 1 > out_size) {
        return -1; // buffer too small
    }

    char *p = out;
    for (int i = 0; i < n; i++) {
        size_t len = strlen(strings[i]);
        memcpy(p, strings[i], len);
        p += len;
    }
    *p = '\0';
    return 0;
}

// ---------- Test Functions ----------
void test_concatenate() {
    // Test 1: empty list
    {
        const char *arr0 = "";  // dummy pointer for NULL
        char *buf0 = malloc(1); // only space for the null terminator
        assert(concatenate(NULL, 0, buf0, 1) == 0);
        assert(strcmp(buf0, "") == 0);
        free(buf0);
    }

    // Test 2: ['x', 'y', 'z'] -> 'xyz'
    {
        const char *arr1[] = {"x", "y", "z"};
        int n1 = 3;
        size_t len1 = 3 + 1; // 3 chars + null
        char *buf1 = malloc(len1);
        assert(concatenate(arr1, n1, buf1, len1) == 0);
        assert(strcmp(buf1, "xyz") == 0);
        free(buf1);
    }

    // Test 3: ['x', 'y', 'z', 'w', 'k'] -> 'xyzwk'
    {
        const char *arr2[] = {"x", "y", "z", "w", "k"};
        int n2 = 5;
        size_t len2 = 5 + 1; // 5 chars + null
        char *buf2 = malloc(len2);
        assert(concatenate(arr2, n2, buf2, len2) == 0);
        assert(strcmp(buf2, "xyzwk") == 0);
        free(buf2);
    }
}

// ---------- Main ----------
int main(void) {
    test_concatenate();
    return 0;
}