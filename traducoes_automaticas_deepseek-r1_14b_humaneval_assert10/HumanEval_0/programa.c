#include <assert.h>
#include <math.h>

int has_close_elements(float numbers[], int length, float threshold) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            float distance = fabs(numbers[i] - numbers[j]);
            if (distance < threshold) {
                return 1;
            }
        }
    }
    return 0;
}

void test_case_1() {
    float numbers[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    float threshold = 0.3;
    assert(has_close_elements(numbers, 6, threshold) == 1);
}

void test_case_2() {
    float numbers[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    float threshold = 0.05;
    assert(has_close_elements(numbers, 6, threshold) == 0);
}

void test_case_3() {
    float numbers[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    float threshold = 0.95;
    assert(has_close_elements(numbers, 5, threshold) == 1);
}

void test_case_4() {
    float numbers[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    float threshold = 0.8;
    assert(has_close_elements(numbers, 5, threshold) == 0);
}

void test_case_5() {
    float numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    float threshold = 0.1;
    assert(has_close_elements(numbers, 6, threshold) == 1);
}

void test_case_6() {
    float numbers[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    float threshold = 1.0;
    assert(has_close_elements(numbers, 5, threshold) == 1);
}

void test_case_7() {
    float numbers[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    float threshold = 0.5;
    assert(has_close_elements(numbers, 5, threshold) == 0);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    test_case_7();
    return 0;
}