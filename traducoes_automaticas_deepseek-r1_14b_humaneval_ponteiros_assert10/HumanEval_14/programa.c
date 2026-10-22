char** all_prefixes_c(char* input, int* size) {
    int len = strlen(input);
    char** result = malloc(len * sizeof(char*));
    for (int i = 0; i < len; i++) {
        int prefix_len = i + 1;
        result[i] = malloc(prefix_len + 1);
        strncpy(result[i], input, prefix_len);
        result[i][prefix_len] = '\0';
    }
    *size = len;
    return result;
}

void assert_arrays_equal(char** a, int size_a, char** b, int size_b) {
    if (size_a != size_b) {
        assert(0);
    }
    for (int i = 0; i < size_a; i++) {
        if (strcmp(a[i], b[i]) != 0) {
            assert(0);
        }
    }
}

int main() {
    // Test 1: empty string
    char input1[] = "";
    int size1;
    char** result1 = all_prefixes_c(input1, &size1);
    assert(size1 == 0);
    free(result1);

    // Test 2: "asdfgh"
    char input2[] = "asdfgh";
    int size2;
    char** result2 = all_prefixes_c(input2, &size2);
    assert(size2 == 6);
    
    // Create expected array dynamically
    char** expected2 = malloc(6 * sizeof(char*));
    expected2[0] = strdup("a");
    expected2[1] = strdup("as");
    expected2[2] = strdup("asd");
    expected2[3] = strdup("asdf");
    expected2[4] = strdup("asdfg");
    expected2[5] = strdup("asdfgh");
    
    assert_arrays_equal(result2, size2, expected2, 6);
    free(result2);
    free(expected2);

    // Test 3: "WWW"
    char input3[] = "WWW";
    int size3;
    char** result3 = all_prefixes_c(input3, &size3);
    assert(size3 == 3);
    
    // Create expected array dynamically
    char** expected3 = malloc(3 * sizeof(char*));
    expected3[0] = strdup("W");
    expected3[1] = strdup("WW");
    expected3[2] = strdup("WWW");
    
    assert_arrays_equal(result3, size3, expected3, 3);
    free(result3);
    free(expected3);

    return 0;
}