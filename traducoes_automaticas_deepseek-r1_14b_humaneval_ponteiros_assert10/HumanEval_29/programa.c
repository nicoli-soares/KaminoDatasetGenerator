#define MAX_STRINGS 1000
#define MAX_STRING_LENGTH 256

int str_starts_with(const char *str, const char *prefix) {
    size_t len = strlen(prefix);
    if (len == 0) return 1;
    if (strlen(str) < len) return 0;
    return strncmp(str, prefix, len) == 0;
}

int filter_by_prefix_c(const char *strings[MAX_STRINGS], const char *prefix, char output[MAX_STRINGS][MAX_STRING_LENGTH]) {
    int count = 0;
    for (int i = 0; i < MAX_STRINGS && strings[i] != NULL; i++) {
        if (str_starts_with(strings[i], prefix)) {
            if (count >= MAX_STRINGS) return -1;
            strncpy(output[count], strings[i], MAX_STRING_LENGTH - 1);
            output[count][MAX_STRING_LENGTH - 1] = '\0';
            count++;
        }
    }
    return count;
}

void test_case_1() {
    const char *input[MAX_STRINGS] = {};
    char output[MAX_STRINGS][MAX_STRING_LENGTH];
    input[0] = "abc";
    input[1] = "bcd";
    input[2] = "cde";
    input[3] = "array";
    const char *prefix = "a";
    int result = filter_by_prefix_c(input, prefix, output);
    assert(result == 2);
    assert(strcmp(output[0], "abc") == 0);
    assert(strcmp(output[1], "array") == 0);
}

void test_case_2() {
    const char *input[MAX_STRINGS] = {};
    char output[MAX_STRINGS][MAX_STRING_LENGTH];
    input[0] = "xxx";
    input[1] = "asd";
    input[2] = "xxy";
    input[3] = "john doe";
    input[4] = "xxxAAA";
    input[5] = "xxx";
    const char *prefix = "xxx";
    int result = filter_by_prefix_c(input, prefix, output);
    assert(result == 3);
    assert(strcmp(output[0], "xxx") == 0);
    assert(strcmp(output[1], "xxxAAA") == 0);
    assert(strcmp(output[2], "xxx") == 0);
}

int main() {
    test_case_1();
    test_case_2();
    return 0;
}