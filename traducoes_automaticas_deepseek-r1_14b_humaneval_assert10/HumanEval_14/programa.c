char** all_prefixes_c(const char* string) {
    if (string == NULL || *string == '\0') {
        return NULL;
    }

    size_t length = strlen(string);
    char** prefixes = malloc(length * sizeof(char*));

    for (size_t i = 0; i < length; i++) {
        prefixes[i] = strndup(string, i + 1);
    }

    return prefixes;
}

void test_all_prefixes() {
    char** result;

    // Test empty string
    result = all_prefixes_c("");
    assert(result == NULL);

    // Test "asdfgh"
    result = all_prefixes_c("asdfgh");
    assert(result != NULL);
    assert(strcmp(result[0], "a") == 0);
    assert(strcmp(result[1], "as") == 0);
    assert(strcmp(result[2], "asd") == 0);
    assert(strcmp(result[3], "asdf") == 0);
    assert(strcmp(result[4], "asdfg") == 0);
    assert(strcmp(result[5], "asdfgh") == 0);
    free(result);

    // Test "WWW"
    result = all_prefixes_c("WWW");
    assert(result != NULL);
    assert(strcmp(result[0], "W") == 0);
    assert(strcmp(result[1], "WW") == 0);
    assert(strcmp(result[2], "WWW") == 0);
    free(result);

    // Test single character
    result = all_prefixes_c("a");
    assert(result != NULL);
    assert(strcmp(result[0], "a") == 0);
    free(result);
}

int main() {
    test_all_prefixes();
    return 0;
}