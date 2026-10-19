typedef struct {
    int value;
} Operation;

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
    assert(below_zero_c(ops, 0) == 0);
}

void test_case_2() {
    int ops[] = {1, 2, -3, 1, 2, -3};
    assert(below_zero_c(ops, 6) == 0);
}

void test_case_3() {
    int ops[] = {1, 2, -4, 5, 6};
    assert(below_zero_c(ops, 5) == 1);
}

void test_case_4() {
    int ops[] = {1, -1, 2, -2, 5, -5, 4, -4};
    assert(below_zero_c(ops, 8) == 0);
}

void test_case_5() {
    int ops[] = {1, -1, 2, -2, 5, -5, 4, -5};
    assert(below_zero_c(ops, 8) == 1);
}

void test_case_6() {
    int ops[] = {1, -2, 2, -2, 5, -5, 4, -4};
    assert(below_zero_c(ops, 8) == 1);
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