#include <stdio.h>
#include <string.h>

typedef struct {
    char chave[256];
    char valor[256];
} ParStringString;

int filter_by_substring_c(char **strings, int strings_size, char *substring, int *result_size) {
    int count = 0;
    for (int i = 0; i < strings_size; i++) {
        char *str = strings[i];
        if (strstr(str, substring) != NULL) {
            count++;
        }
    }
    *result_size = count;
    return 0;
}

int main() {
    char *strings[] = {"abc", "bacd", "cde", "array"};
    int strings_size = sizeof(strings) / sizeof(strings[0]);
    char *substring = "a";
    int result_size;
    int status = filter_by_substring_c(strings, strings_size, substring, &result_size);
    assert(status == 0);

    char *expected[] = {"abc", "bacd", "array"};
    assert(result_size == 3);
    for (int i = 0; i < result_size; i++) {
        assert(strcmp(strings[i], expected[i]) == 0);
    }

    char *strings1[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    int strings_size1 = sizeof(strings1) / sizeof(strings1[0]);
    substring = "xxx";
    result_size = 0;
    status = filter_by_substring_c(strings1, strings_size1, substring, &result_size);
    assert(status == 0);

    char *expected1[] = {"xxx", "xxxAAA", "xxx"};
    assert(result_size == 3);
    for (int i = 0; i < result_size; i++) {
        assert(strcmp(strings1[i], expected1[i]) == 0);
    }

    char *strings2[] = {"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"};
    int strings_size2 = sizeof(strings2) / sizeof(strings2[0]);
    substring = "xx";
    result_size = 0;
    status = filter_by_substring_c(strings2, strings_size2, substring, &result_size);
    assert(status == 0);

    char *expected2[] = {"xxx", "aaaxxy", "xxxAAA", "xxx"};
    assert(result_size == 4);
    for (int i = 0; i < result_size; i++) {
        assert(strcmp(strings2[i], expected2[i]) == 0);
    }

    return 0;
}