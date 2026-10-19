#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char **strings;
    char *substring;
} FilterConfig;

char** filter_strings(char** strings, const char* substring, int* size) {
    if (strings == NULL || substring == NULL) {
        return NULL;
    }

    int count = 0;
    // First pass: count the number of matches
    for (int i = 0; strings[i] != NULL; i++) {
        if (strstr(strings[i], substring) != NULL) {
            count++;
        }
    }

    // If no matches, return NULL or empty array
    if (count == 0) {
        return NULL;
    }

    // Allocate memory for the result array
    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    // Second pass: fill the result array
    int index = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        if (strstr(strings[i], substring) != NULL) {
            result[index] = strdup(strings[i]);
            if (result[index] == NULL) {
                free(result);
                return NULL;
            }
            index++;
        }
    }

    // Set the size
    *size = count;

    return result;
}

void free_result(char** result) {
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main() {
    char* strings[] = {"abc", "bacd", "cde", "array", NULL};
    const char* substring = "a";
    char** result;
    int size;

    result = filter_strings(strings, substring, &size);
    if (result == NULL) {
        // Handle error
        return 1;
    }

    // Verify the results
    assert(size == 3);
    assert(strcmp(result[0], "abc") == 0);
    assert(strcmp(result[1], "bacd") == 0);
    assert(strcmp(result[2], "array") == 0);

    free_result(result);

    return 0;
}