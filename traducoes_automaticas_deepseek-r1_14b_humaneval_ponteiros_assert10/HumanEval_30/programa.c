typedef struct {
    int value;
} NumberElement;

int get_positive_c(const int input[], int n, int output[]) {
    int pos = 0;
    for (int i = 0; i < n; i++) {
        if (input[i] > 0) {
            output[pos++] = input[i];
        }
    }
    return pos;
}

void test_case_1() {
    const int input[] = {-1, 2, -4, 5, 6};
    int expected[] = {2, 5, 6};
    int output[3];
    int size = get_positive_c(input, 5, output);
    assert(size == 3);
    assert(output[0] == 2 && output[1] == 5 && output[2] == 6);
}

void test_case_2() {
    const int input[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int expected[] = {5, 3, 2, 3, 9, 123, 1};
    int output[7];
    int size = get_positive_c(input, 11, output);
    assert(size == 7);
    assert(output[0] == 5 && output[1] == 3 && output[2] == 2 && output[3] == 3 && output[4] == 9 && output[5] == 123 && output[6] == 1);
}

void test_case_3() {
    const int input[] = {-1, -2};
    int expected[] = {};
    int output[2];
    int size = get_positive_c(input, 2, output);
    assert(size == 0);
}

void test_case_4() {
    const int input[] = {};
    int output[1];
    int size = get_positive_c(input, 0, output);
    assert(size == 0);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}