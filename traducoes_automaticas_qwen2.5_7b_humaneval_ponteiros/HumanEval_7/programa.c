#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
    const char *text;
} String;

typedef struct {
    String *strings;
    int count;
} StringList;

int filter_by_substring_c(StringList strings, const char *substring, StringList *filtered) {
    filtered->count = 0;
    for (int i = 0; i < strings.count; i++) {
        const char *str = strings.strings[i].text;
        if (strstr(str, substring) != NULL) {
            filtered->count++;
        }
    }
    filtered->strings = (String *)malloc(filtered->count * sizeof(String));
    if (filtered->strings == NULL) {
        return -1; // Memory allocation failed
    }
    int j = 0;
    for (int i = 0; i < strings.count; i++) {
        const char *str = strings.strings[i].text;
        if (strstr(str, substring) != NULL) {
            filtered->strings[j].text = strdup(str);
            if (filtered->strings[j].text == NULL) {
                free(filtered->strings);
                return -2; // Memory allocation failed for strdup
            }
            j++;
        }
    }
    return 0;
}

void test_filter_by_substring_c() {
    StringList strings = { .strings = (String[]) {
        { .text = "abc" },
        { .text = "bacd" },
        { .text = "cde" },
        { .text = "array" },
    }, .count = 4 };
    StringList filtered;
    assert(filter_by_substring_c(strings, "a", &filtered) == 0);
    assert(filtered.count == 3);
    assert(strcmp(filtered.strings[0].text, "abc") == 0);
    assert(strcmp(filtered.strings[1].text, "bacd") == 0);
    assert(strcmp(filtered.strings[2].text, "array") == 0);
    for (int i = 0; i < filtered.count; i++) {
        free(filtered.strings[i].text);
    }
    free(filtered.strings);
}

int main() {
    test_filter_by_substring_c();
    return 0;
}