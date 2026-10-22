#include <string.h>
#include <stdlib.h>
#include <assert.h>

char* flip_case_c(char* string) {
    char* result = malloc(strlen(string) + 1);
    if (!result) return NULL;
    for (int i = 0; string[i] != '\0'; i++) {
        if (isupper(string[i])) {
            result[i] = tolower(string[i]);
        } else if (islower(string[i])) {
            result[i] = toupper(string[i]);
        } else {
            result[i] = string[i];
        }
    }
    result[strlen(string)] = '\0';
    return result;
}

int main() {
    // Test 1: Empty string
    assert(strcmp(flip_case_c(""), "") == 0);
    
    // Test 2: Mixed case with punctuation
    assert(strcmp(flip_case_c("Hello!"), "hELLO!") == 0);
    
    // Test 3: Mixed case sentence
    assert(strcmp(flip_case_c("These violent delights have violent ends"), "tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS") == 0);
}