typedef struct {
    const char *note;
    int duration;
} NoteWithDuration;

NoteWithDuration noteMap[] = {
    {"o", 4},
    {"o|", 2},
    {".|", 1}
};

int parse_music_c(const char *musicString, int *result, size_t size) {
    int index = 0;
    if (musicString == NULL || size == 0) return 0;
    
    char *str_copy = strdup(musicString);
    char *token = strtok(str_copy, " ");
    while (token != NULL && index < size) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(token, noteMap[i].note) == 0) {
                result[index++] = noteMap[i].duration;
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    free(str_copy);
    return index;
}

void test_case_1() {
    const char *input = "o o| .| o| o| .| .| .| .| o o";
    int expected[] = {4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4};
    int *result = malloc(128 * sizeof(int));
    if (result == NULL) return;
    int expected_size = sizeof(expected) / sizeof(expected[0]);
    int count = parse_music_c(input, result, expected_size);
    assert(count == expected_size);
    for (int i = 0; i < count; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

void test_case_2() {
    int *result = malloc(128 * sizeof(int));
    if (result == NULL) return;
    assert(parse_music_c("", result, 0) == 0);
    free(result);
}

void test_case_3() {
    const char *input = "o o o o";
    int expected[] = {4,4,4,4};
    int *result = malloc(128 * sizeof(int));
    if (result == NULL) return;
    int expected_size = sizeof(expected) / sizeof(expected[0]);
    int count = parse_music_c(input, result, expected_size);
    assert(count == expected_size);
    for (int i = 0; i < count; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

void test_case_4() {
    const char *input = "o| o| .| .| o o o o";
    int expected[] = {2,2,1,1,4,4,4,4};
    int *result = malloc(128 * sizeof(int));
    if (result == NULL) return;
    int expected_size = sizeof(expected) / sizeof(expected[0]);
    int count = parse_music_c(input, result, expected_size);
    assert(count == expected_size);
    for (int i = 0; i < count; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

void test_case_5() {
    const char *input = "o| .| o| .| o o| o o|";
    int expected[] = {2,1,2,1,4,2,4,2};
    int *result = malloc(128 * sizeof(int));
    if (result == NULL) return;
    int expected_size = sizeof(expected) / sizeof(expected[0]);
    int count = parse_music_c(input, result, expected_size);
    assert(count == expected_size);
    for (int i = 0; i < count; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    return 0;
}