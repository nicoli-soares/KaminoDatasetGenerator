int below_zero_c(int operations[], int size) {
    int balance = 0;
    for (int i = 0; i < size; i++) {
        balance += operations[i];
        if (balance < 0) {
            return 1;
        }
    }
    return 0;
}

void test_case_1() {
    int ops[] = {};
    int expected = 0;
    assert(below_zero_c(ops, sizeof(ops)/sizeof(ops[0])) == expected);
}

void test_case_2() {
    int ops[] = {1, 2, -3, 1, 2, -3};
    int expected = 0;
    assert(below_zero_c(ops, sizeof(ops)/sizeof(ops[0])) == expected);
}

void test_case_3() {
    int ops[] = {1, 2, -4, 5, 6};
    int expected = 1;
    assert(below_zero_c(ops, sizeof(ops)/sizeof(ops[0])) == expected);
}

void test_case_4() {
    int ops[] = {1, -1, 2, -2, 5, -5, 4, -4};
    int expected = 0;
    assert(below_zero_c(ops, sizeof(ops)/sizeof(ops[0])) == expected);
}

void test_case_5() {
    int ops[] = {1, -1, 2, -2, 5, -5, 4, -5};
    int expected = 1;
    assert(below_zero_c(ops, sizeof(ops)/sizeof(ops[0])) == expected);
}

void test_case_6() {
    int ops[] = {1, -2, 2, -2, 5, -5, 4, -4};
    int expected = 1;
    assert(below_zero_c(ops, sizeof(ops)/sizeof(ops[0])) == expected);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    return 0;
}