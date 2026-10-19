int* intersperse_c(int* numbers, int numbers_len, int delimeter) {
    if (numbers_len == 0) {
        return NULL;
    }
    int result_len = 2 * (numbers_len - 1) + 1;
    int* result = malloc(result_len * sizeof(int));
    int result_index = 0;
    for (int i = 0; i < numbers_len - 1; i++) {
        result[result_index++] = numbers[i];
        result[result_index++] = delimeter;
    }
    result[result_index++] = numbers[numbers_len - 1];
    return result;
}

void test1() {
    int numbers[] = {};
    int numbers_len = 0;
    int delimeter = 7;
    int* result = intersperse_c(numbers, numbers_len, delimeter);
    assert(result == NULL);
    if (result != NULL) {
        free(result);
    }
}

void test2() {
    int numbers[] = {5,6,3,2};
    int numbers_len = 4;
    int delimeter = 8;
    int* result = intersperse_c(numbers, numbers_len, delimeter);
    assert(result != NULL);
    assert(result[0] ==5);
    assert(result[1] ==8);
    assert(result[2] ==6);
    assert(result[3] ==8);
    assert(result[4] ==3);
    assert(result[5] ==8);
    assert(result[6] ==2);
    free(result);
}

void test3() {
    int numbers[] = {2,2,2};
    int numbers_len =3;
    int delimeter =2;
    int* result = intersperse_c(numbers, numbers_len, delimeter);
    assert(result != NULL);
    assert(result[0] ==2);
    assert(result[1] ==2);
    assert(result[2] ==2);
    assert(result[3] ==2);
    assert(result[4] ==2);
    free(result);
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}