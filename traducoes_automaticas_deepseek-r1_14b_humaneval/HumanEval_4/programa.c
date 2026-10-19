double mean_absolute_deviation(double numbers[], int n) {
    if (n == 0) {
        return 0.0;
    }
    double sum = 0.0;
    double mean = 0.0;
    double mad = 0.0;
    
    for (int i = 0; i < n; i++) {
        sum += numbers[i];
    }
    mean = sum / n;
    
    sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += fabs(numbers[i] - mean);
    }
    
    mad = sum / n;
    return mad;
}

static void test_case_1() {
    double numbers[] = {1.0, 2.0, 3.0};
    double result = mean_absolute_deviation(numbers, 3);
    assert(fabs(result - (2.0/3.0)) < 1e-6);
}

static void test_case_2() {
    double numbers[] = {1.0, 2.0, 3.0, 4.0};
    double result = mean_absolute_deviation(numbers, 4);
    assert(fabs(result - 1.0) < 1e-6);
}

static void test_case_3() {
    double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = mean_absolute_deviation(numbers, 5);
    assert(fabs(result - (6.0/5.0)) < 1e-6);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}