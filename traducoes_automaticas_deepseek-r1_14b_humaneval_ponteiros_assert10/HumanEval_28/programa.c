char* concatenate_c(const char* strings[], int n) {
    size_t total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += strlen(strings[i]);
    }
    char* result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }
    size_t current_position = 0;
    for (int i = 0; i < n; i++) {
        strcpy(result + current_position, strings[i]);
        current_position += strlen(strings[i]);
    }
    result[total_length] = '\0';
    return result;
}

int main() {
    // Test case 1: empty list
    const char* strings1[] = {};
    char* result1 = concatenate_c(strings1, 0);
    assert(result1 != NULL && strcmp(result1, "") == 0);
    free(result1);

    // Test case 2: ['x', 'y', 'z']
    const char* strings2[] = {"x", "y", "z"};
    char* result2 = concatenate_c(strings2, 3);
    assert(result2 != NULL && strcmp(result2, "xyz") == 0);
    free(result2);

    // Test case 3: ['x', 'y', 'z', 'w', 'k']
    const char* strings3[] = {"x", "y", "z", "w", "k"};
    char* result3 = concatenate_c(strings3, 5);
    assert(result3 != NULL && strcmp(result3, "xyzwk") == 0);
    free(result3);

    return 0;
}