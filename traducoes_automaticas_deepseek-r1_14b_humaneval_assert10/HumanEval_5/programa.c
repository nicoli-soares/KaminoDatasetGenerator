int* intersperse_c(int* numbers, int numbers_len, int delimeter) {
    if (numbers == NULL || numbers_len == 0) {
        return NULL;
    }
    
    int result_size = 2 * numbers_len - 1;
    int* result = (int*)malloc(result_size * sizeof(int));
    
    for (int i = 0; i < numbers_len - 1; i++) {
        result[i * 2] = numbers[i];
        result[i * 2 + 1] = delimeter;
    }
    
    result[result_size - 1] = numbers[numbers_len - 1];
    
    return result;
}

static int expected_case_2[] = {5, 8, 6, 8, 3, 8, 2};
static int expected_case_3[] = {2, 2, 2, 2, 2};

void test_case_1() {
    int numbers[] = {};
    int delimeter = 7;
    int* result = intersperse_c(numbers, 0, delimeter);
    assert(result == NULL);
}

void test_case_2() {
    int numbers[] = {5, 6, 3, 2};
    int delimeter = 8;
    int* result = intersperse_c(numbers, 4, delimeter);
    int* expected = expected_case_2;
    for (int i = 0; i < 7; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

void test_case_3() {
    int numbers[] = {2, 2, 2};
    int delimeter = 2;
    int* result = intersperse_c(numbers, 3, delimeter);
    int* expected = expected_case_3;
    for (int i = 0; i < 5; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}