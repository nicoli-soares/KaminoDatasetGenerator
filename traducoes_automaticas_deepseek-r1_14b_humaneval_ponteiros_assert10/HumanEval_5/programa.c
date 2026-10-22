typedef struct {
    int value;
} IntValue;

int intersperse_c(int numbers[], int size, int delimeter, int result[]) {
    if (size == 0) {
        return 0;
    }

    int pos = 0;

    for (int i = 0; i < size - 1; i++) {
        result[pos++] = numbers[i];
        result[pos++] = delimeter;
    }

    result[pos] = numbers[size - 1];
    return pos + 1;
}

void test_intersperse_c() {
    int test1_input[] = {};
    int test1_output[1] = {};
    assert(intersperse_c(test1_input, 0, 7, test1_output) == 0);

    int test2_input[] = {5, 6, 3, 2};
    int test2_output[7] = {}; // Expected size is 2*4-1=7
    assert(intersperse_c(test2_input, 4, 8, test2_output) == 7);
    assert(test2_output[0] == 5);
    assert(test2_output[1] == 8);
    assert(test2_output[2] == 6);
    assert(test2_output[3] == 8);
    assert(test2_output[4] == 3);
    assert(test2_output[5] == 8);
    assert(test2_output[6] == 2);

    int test3_input[] = {2, 2, 2};
    int test3_output[5] = {}; // Expected size is 2*3-1=5
    assert(intersperse_c(test3_input, 3, 2, test3_output) == 5);
    assert(test3_output[0] == 2);
    assert(test3_output[1] == 2);
    assert(test3_output[2] == 2);
    assert(test3_output[3] == 2);
    assert(test3_output[4] == 2);
}

int main() {
    test_intersperse_c();
    return 0;
}