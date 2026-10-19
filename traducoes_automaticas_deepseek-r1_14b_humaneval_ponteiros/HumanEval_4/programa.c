#include <assert.h>
#include <math.h>

double mean_absolute_deviation_c(double numbers[], int n) {
    double mean = 0.0;
    for (int i = 0; i < n; i++) {
        mean += numbers[i];
    }
    mean /= n;
    
    double mad = 0.0;
    for (int i = 0; i < n; i++) {
        mad += fabs(numbers[i] - mean);
    }
    mad /= n;
    
    return mad;
}

void test_case_1(double numbers[], int n, double expected) {
    assert(fabs(mean_absolute_deviation_c(numbers, n) - expected) < 1e-6);
}

int main() {
    // Test case 1
    double arr1[] = {1.0, 2.0, 3.0};
    int len1 = sizeof(arr1)/sizeof(arr1[0]);
    test_case_1(arr1, len1, 2.0/3.0);
    
    // Test case 2
    double arr2[] = {1.0, 2.0, 3.0, 4.0};
    int len2 = sizeof(arr2)/sizeof(arr2[0]);
    test_case_1(arr2, len2, 1.0);
    
    // Test case 3
    double arr3[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int len3 = sizeof(arr3)/sizeof(arr3[0]);
    test_case_1(arr3, len3, 6.0/5.0);
    
    return 0;
}