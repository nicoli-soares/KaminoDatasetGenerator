#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Function to concatenate an array of strings into a single string */
char* concatenate(char** strings, int count) {
    unsigned int total_len = 0;
    for (int i = 0; i < count; i++) {
        total_len += (unsigned int)strlen(strings[i]);
    }
    /* Allocate memory for the concatenated string plus null terminator */
    char* result = (char*)malloc(total_len + 1);
    if (!result) return NULL; /* Allocation failed */
    char* p = result;
    for (int i = 0; i < count; i++) {
        unsigned int len = (unsigned int)strlen(strings[i]);
        memcpy(p, strings[i], len);
        p += len;
    }
    *p = '\0';
    return result;
}

/* Test harness that checks the concatenate function against the original tests */
void check(char* (*candidate)(char**, int)) {
    /* Test 1: empty list */
    {
        char* res = candidate(NULL, 0);
        assert(res != NULL);
        assert(strcmp(res, "") == 0);
        free(res);
    }
    /* Test 2: ['x', 'y', 'z'] */
    {
        char* arr[] = {"x", "y", "z"};
        char* res = candidate(arr, 3);
        assert(res != NULL);
        assert(strcmp(res, "xyz") == 0);
        free(res);
    }
    /* Test 3: ['x', 'y', 'z', 'w', 'k'] */
    {
        char* arr[] = {"x", "y", "z", "w", "k"};
        char* res = candidate(arr, 5);
        assert(res != NULL);
        assert(strcmp(res, "xyzwk") == 0);
        free(res);
    }
}

/* Main function that runs all tests */
int main(void) {
    check(concatenate);
    return 0;
}