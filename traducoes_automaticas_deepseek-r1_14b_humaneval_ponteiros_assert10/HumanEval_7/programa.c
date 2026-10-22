#include <string.h>
#include <assert.h>

typedef struct {
    char *str;
    size_t length;
} StringPair;

size_t get_string_length(const char *str) {
    return strlen(str);
}

StringPair *filter_by_substring_c(StringPair *strings, size_t num_strings, const char *substring, size_t substring_length) {
    size_t result_count = 0;
    StringPair *result = malloc(num_strings * sizeof(StringPair));
    
    for (size_t i = 0; i < num_strings; i++) {
        if (strstr(strings[i].str, substring) != NULL) {
            result[result_count].str = strings[i].str;
            result[result_count].length = strings[i].length;
            result_count++;
        }
    }
    
    return result;
}

static void test_case_1() {
    StringPair input[] = {};
    const char *substring = "a";
    size_t substring_length = 1;
    
    StringPair *output = filter_by_substring_c(input, 0, substring, substring_length);
    assert(output == NULL || output[0].str == NULL);
}

static void test_case_2() {
    StringPair input[] = {
        {"abc", get_string_length("abc")},
        {"bacd", get_string_length("bacd")},
        {"cde", get_string_length("cde")},
        {"array", get_string_length("array")},
    };
    const char *substring = "a";
    size_t substring_length = 1;
    
    StringPair *output = filter_by_substring_c(input, 4, substring, substring_length);
    assert(output != NULL);
    assert(strcmp(output[0].str, "abc") == 0 && output[0].length == 3);
    assert(strcmp(output[1].str, "bacd") == 0 && output[1].length == 4);
    assert(strcmp(output[2].str, "array") == 0 && output[2].length == 5);
    free(output);
}

static void test_case_3() {
    StringPair input[] = {
        {"xxx", get_string_length("xxx")},
        {"asd", get_string_length("asd")},
        {"xxy", get_string_length("xxy")},
        {"john doe", get_string_length("john doe")},
        {"xxxAAA", get_string_length("xxxAAA")},
        {"xxx", get_string_length("xxx")},
    };
    const char *substring = "xxx";
    size_t substring_length = 3;
    
    StringPair *output = filter_by_substring_c(input, 6, substring, substring_length);
    assert(output != NULL);
    assert(strcmp(output[0].str, "xxx") == 0 && output[0].length == 3);
    assert(strcmp(output[1].str, "xxxAAA") == 0 && output[1].length == 6);
    assert(strcmp(output[2].str, "xxx") == 0 && output[2].length == 3);
    free(output);
}

static void test_case_4() {
    StringPair input[] = {
        {"xxx", get_string_length("xxx")},
        {"asd", get_string_length("asd")},
        {"aaaxxy", get_string_length("aaaxxy")},
        {"john doe", get_string_length("john doe")},
        {"xxxAAA", get_string_length("xxxAAA")},
        {"xxx", get_string_length("xxx")},
    };
    const char *substring = "xx";
    size_t substring_length = 2;
    
    StringPair *output = filter_by_substring_c(input, 6, substring, substring_length);
    assert(output != NULL);
    assert(strcmp(output[0].str, "xxx") == 0 && output[0].length == 3);
    assert(strcmp(output[1].str, "aaaxxy") == 0 && output[1].length == 6);
    assert(strcmp(output[2].str, "xxxAAA") == 0 && output[2].length == 6);
    assert(strcmp(output[3].str, "xxx") == 0 && output[3].length == 3);
    free(output);
}

static void test_case_5() {
    StringPair input[] = {
        {"grunt", get_string_length("grunt")},
        {"trumpet", get_string_length("trumpet")},
        {"prune", get_string_length("prune")},
        {"gruesome", get_string_length("gruesome")},
    };
    const char *substring = "run";
    size_t substring_length = 3;
    
    StringPair *output = filter_by_substring_c(input, 4, substring, substring_length);
    assert(output != NULL);
    assert(strcmp(output[0].str, "grunt") == 0 && output[0].length == 5);
    assert(strcmp(output[1].str, "prune") == 0 && output[1].length == 5);
    free(output);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    return 0;
}