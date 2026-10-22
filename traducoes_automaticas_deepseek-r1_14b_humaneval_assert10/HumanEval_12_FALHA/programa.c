#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char* longest(const char** strings, int length) {
    if (length == 0) {
        return NULL;
    }
    
    int maxlen = -1;
    for (int i = 0; i < length; i++) {
        if (strlen(strings[i]) > maxlen) {
            maxlen = strlen(strings[i]);
        }
    }
    
    for (int i = 0; i < length; i++) {
        if (strlen(strings[i]) == maxlen) {
            return strings[i];
        }
    }
}

void test_longest() {
    // Test case 1: empty list
    assert(longest(NULL, 0) == NULL);
    
    // Test case 2: all single character strings
    const char* test2[] = {"x", "y", "z"};
    assert(strcmp(longest(test2, 3), "x") == 0);
    
    // Test case 3: varying string lengths
    const char* test3[] = {"x", "yyy", "zzzz", "www", "kkkk", "abc"};
    assert(strcmp(longest(test3, 6), "zzzz") == 0);
    
    // Additional test case: all empty strings
    const char* test4[] = {"", "", ""};
    assert(strcmp(longest(test4, 3), "") == 0);
}

int main() {
    test_longest();
    return EXIT_SUCCESS;
}