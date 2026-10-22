#include <assert.h>
#include <stdbool.h>

bool below_zero(int operations[], int size) {
    int balance = 0;
    for (int i = 0; i < size; i++) {
        balance += operations[i];
        if (balance < 0) {
            return true;
        }
    }
    return false;
}

void test_case_1() {
    int empty[] = {};
    assert(below_zero(empty, 0) == false);
}

void test_case_2() {
    int ops[] = {1, 2, -3, 1, 2, -3};
    assert(below_zero(ops, 6) == false);
}

void test_case_3() {
    int ops[] = {1, 2, -4, 5, 6};
    assert(below_zero(ops, 5) == true);
}

void test_case_4() {
    int ops[] = {1, -1, 2, -2, 5, -5, 4, -4};
    assert(below_zero(ops, 8) == false);
}

void test_case_5() {
    int ops[] = {1, -1, 2, -2, 5, -5, 4, -5};
    assert(below_zero(ops, 8) == true);
}

void test_case_6() {
    int ops[] = {1, -2, 2, -2, 5, -5, 4, -4};
    assert(below_zero(ops, 8) == true);
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