#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* concatenate_c(char** strings, int len) {
    if (len == 0) {
        return strings == NULL ? NULL : "";
    }
    
    size_t total_length = 0;
    for (int i = 0; i < len; i++) {
        total_length += strlen(strings[i]);
    }
    
    char* result = malloc(total_length + 1);
    result[0] = '\0';
    
    char* current = result;
    for (int i = 0; i < len; i++) {
        strncat(current, strings[i], strlen(strings[i]));
        current += strlen(strings[i]);
    }
    
    return result;
}

void test_concatenate() {
    assert(concatenate_c(NULL, 0) == NULL);  // Test case where both strings and len are 0
    
    char* test1[] = {"x", "y", "z"};
    assert(strcmp(concatenate_c(test1, 3), "xyz") == 0);
    
    char* test2[] = {"x", "y", "z", "w", "k"};
    assert(strcmp(concatenate_c(test2, 5), "xyzwk") == 0);
}

int main() {
    test_concatenate();
    return 0;
}