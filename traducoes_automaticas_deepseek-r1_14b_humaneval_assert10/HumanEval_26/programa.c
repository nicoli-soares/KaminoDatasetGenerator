typedef struct {
    int num;
    int count;
} ElementCount;

int* remove_duplicates_c(int* input, int size) {
    if (input == NULL || size == 0) {
        return NULL;
    }

    // Preallocate array to store counts
    ElementCount* counts = (ElementCount*)malloc(size * sizeof(ElementCount));
    if (counts == NULL) {
        return NULL;
    }

    // Count occurrences
    for (int i = 0; i < size; i++) {
        int num = input[i];
        counts[i].num = num;
        counts[i].count = 0;
        for (int j = 0; j < size; j++) {
            if (input[j] == num) {
                counts[i].count++;
            }
        }
    }

    // Build result
    int result_size = 0;
    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        free(counts);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (counts[i].count == 1) {
            result[result_size++] = input[i];
        }
    }

    free(counts);
    return result;
}

void test_empty() {
    int* result = remove_duplicates_c(NULL, 0);
    assert(result == NULL);
}

void test_all_unique() {
    int input[] = {1, 2, 3, 4};
    int size = sizeof(input)/sizeof(input[0]);
    int* result = remove_duplicates_c(input, size);
    assert(result != NULL);
    assert(result[0] == 1 && result[1] == 2 && result[2] == 3 && result[3] == 4);
    free(result);
}

void test_duplicates() {
    int input[] = {1, 2, 3, 2, 4, 3, 5};
    int size = sizeof(input)/sizeof(input[0]);
    int* result = remove_duplicates_c(input, size);
    assert(result != NULL);
    assert(result[0] == 1 && result[1] == 4 && result[2] == 5);
    free(result);
}

int main() {
    test_empty();
    test_all_unique();
    test_duplicates();
    return 0;
}