typedef struct {
    char *word;
    int value;
} KeyValue;

int get_value(const char *word) {
    if (strcmp(word, "zero") == 0) return 0;
    if (strcmp(word, "one") == 0) return 1;
    if (strcmp(word, "two") == 0) return 2;
    if (strcmp(word, "three") == 0) return 3;
    if (strcmp(word, "four") == 0) return 4;
    if (strcmp(word, "five") == 0) return 5;
    if (strcmp(word, "six") == 0) return 6;
    if (strcmp(word, "seven") == 0) return 7;
    if (strcmp(word, "eight") == 0) return 8;
    if (strcmp(word, "nine") == 0) return 9;
    return -1;
}

int compare_key_value(const void *a, const void *b) {
    const KeyValue *keyA = a;
    const KeyValue *keyB = b;
    return keyA->value - keyB->value;
}

char* sort_numbers_c(const char *input) {
    if (input == NULL || strlen(input) == 0) return strdup("");

    char *token = NULL;
    char *str = strdup(input);
    size_t len = strlen(str);
    char *pos = NULL;
    size_t count = 0;

    // First pass to count valid tokens
    while ((token = strtok_r(str, " ", &pos)) != NULL) {
        int value = get_value(token);
        if (value != -1) {
            count++;
        }
    }

    // Allocate memory for the values
    KeyValue *values = malloc(count * sizeof(KeyValue));
    pos = NULL;  // Reset position pointer

    // Second pass to populate values
    while ((token = strtok_r(str, " ", &pos)) != NULL) {
        int value = get_value(token);
        if (value != -1) {
            values[count].value = value;
            values[count].word = strdup(token);
            count++;
        }
    }

    // Sort the values
    qsort(values, count, sizeof(KeyValue), compare_key_value);

    // Build the result string
    char *result = malloc(1);
    for (size_t i = 0; i < count; i++) {
        if (i > 0) {
            strcat(result, " ");
        }
        strcat(result, values[i].word);
    }

    // Free allocated memory
    free(str);
    free(values);

    return result;
}

void test1() {
    assert(strcmp(sort_numbers_c(""), "") == 0);
}

void test2() {
    assert(strcmp(sort_numbers_c("three"), "three") == 0);
}

void test3() {
    assert(strcmp(sort_numbers_c("three five nine"), "three five nine") == 0);
}

void test4() {
    assert(strcmp(sort_numbers_c("five zero four seven nine eight"), "zero four five seven eight nine") == 0);
}

void test5() {
    assert(strcmp(sort_numbers_c("six five four three two one zero"), "zero one two three four five six") == 0);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}