#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Struct to hold a list of strings returned by filter_by_prefix
typedef struct {
    char **items; // array of string pointers
    int count;    // number of strings in the list
} StringList;

// Helper function to duplicate a string (like strdup)
static char* duplicate_string(const char *s) {
    size_t len = strlen(s);
    char *dup = malloc(len + 1);
    if (dup != NULL) {
        memcpy(dup, s, len + 1);
    }
    return dup;
}

// filter_by_prefix: returns a StringList containing only strings that start with the given prefix
StringList filter_by_prefix(char **strings, int count, const char *prefix) {
    // Allocate maximum possible size
    char **result = NULL;
    int result_count = 0;
    size_t preflen = strlen(prefix);

    if (count > 0) {
        result = malloc(count * sizeof(char *));
    }

    for (int i = 0; i < count; ++i) {
        if (strncmp(strings[i], prefix, preflen) == 0) {
            result[result_count++] = duplicate_string(strings[i]);
        }
    }

    // Reallocate to exact size if necessary
    if (result_count != count) {
        char **tmp = realloc(result, result_count * sizeof(char *));
        if (tmp != NULL || result_count == 0) {
            result = tmp;
        }
    }

    StringList output = {result, result_count};
    return output;
}

// Helper to free a StringList
static void free_string_list(StringList sl) {
    for (int i = 0; i < sl.count; ++i) {
        free(sl.items[i]);
    }
    free(sl.items);
}

// Test function similar to the Python check()
void check(StringList (*candidate)(char**,int,const char*)) {
    // Test with an empty input list
    StringList res1 = candidate(NULL, 0, "john");
    assert(res1.count == 0);
    free_string_list(res1);

    // Test with a list containing several strings
    char *arr[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    StringList res2 = candidate(arr, 6, "xxx");
    assert(res2.count == 3);
    assert(strcmp(res2.items[0], "xxx") == 0);
    assert(strcmp(res2.items[1], "xxxAAA") == 0);
    assert(strcmp(res2.items[2], "xxx") == 0);
    free_string_list(res2);
}

// Main function to run the tests
int main(void) {
    check(filter_by_prefix);
    return 0;
}