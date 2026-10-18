typedef struct {
    double* numbers;
    int size;
    double threshold;
} NumberCheck;

int has_close_elements_c(double* numbers, int size, double threshold) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            double distance = fabs(numbers[i] - numbers[j]);
            if (distance < threshold) {
                return 1;
            }
        }
    }
    return 0;
}

void test1() {
    double nums[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 0.3;
    if (has_close_elements_c(nums, size, threshold) != 1) {
        printf("Test 1 failed\n");
    }
}

void test2() {
    double nums[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 0.05;
    if (has_close_elements_c(nums, size, threshold) != 0) {
        printf("Test 2 failed\n");
    }
}

void test3() {
    double nums[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 0.95;
    if (has_close_elements_c(nums, size, threshold) != 1) {
        printf("Test 3 failed\n");
    }
}

void test4() {
    double nums[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 0.8;
    if (has_close_elements_c(nums, size, threshold) != 0) {
        printf("Test 4 failed\n");
    }
}

void test5() {
    double nums[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 0.1;
    if (has_close_elements_c(nums, size, threshold) != 1) {
        printf("Test 5 failed\n");
    }
}

void test6() {
    double nums[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 1.0;
    if (has_close_elements_c(nums, size, threshold) != 1) {
        printf("Test 6 failed\n");
    }
}

void test7() {
    double nums[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    int size = sizeof(nums)/sizeof(nums[0]);
    double threshold = 0.5;
    if (has_close_elements_c(nums, size, threshold) != 0) {
        printf("Test 7 failed\n");
    }
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    return 0;
}