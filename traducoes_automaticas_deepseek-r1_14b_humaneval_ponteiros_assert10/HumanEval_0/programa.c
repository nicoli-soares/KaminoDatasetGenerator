typedef struct {
    double number;
} NumberElement;

int has_close_elements_c(double numbers[], int n, double threshold) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double distance = fabs(numbers[i] - numbers[j]);
                if (distance < threshold) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    // Test case 1
    double test1[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    assert(has_close_elements_c(test1, n1, 0.3) == 1);

    // Test case 2
    double test2[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    assert(has_close_elements_c(test2, n2, 0.05) == 0);

    // Test case 3
    double test3[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    assert(has_close_elements_c(test3, n3, 0.95) == 1);

    // Test case 4
    double test4[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    assert(has_close_elements_c(test4, n4, 0.8) == 0);

    // Test case 5
    double test5[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    assert(has_close_elements_c(test5, n5, 0.1) == 1);

    // Test case 6
    double test6[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    int n6 = sizeof(test6) / sizeof(test6[0]);
    assert(has_close_elements_c(test6, n6, 1.0) == 1);

    // Test case 7
    double test7[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    int n7 = sizeof(test7) / sizeof(test7[0]);
    assert(has_close_elements_c(test7, n7, 0.5) == 0);

    return 0;
}