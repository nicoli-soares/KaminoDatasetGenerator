char* longest(char* strings[], int size) {
    if (size == 0) {
        return NULL;
    }

    int max_len = 0;
    for (int i = 0; i < size; i++) {
        int current_len = strlen(strings[i]);
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    for (int i = 0; i < size; i++) {
        if (strlen(strings[i]) == max_len) {
            return strings[i];
        }
    }

    return NULL;
}

void test_longest(void) {
    char* test_case1[] = {};
    assert(longest(test_case1, 0) == NULL);

    char* test_case2[] = {"x", "y", "z"};
    char* result = longest(test_case2, 3);
    assert(strcmp(result, "x") == 0);

    char* test_case3[] = {"x", "yyy", "zzzz", "www", "kkkk", "abc"};
    result = longest(test_case3, 6);
    assert(strcmp(result, "zzzz") == 0);
}

int main() {
    test_longest();
    return 0;
}