#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Definition of the rescale_to_unit function
int rescale_to_unit(const double *numbers, int len, double *out) {
    // The function expects at least two numbers
    if (len < 2) {
        return -1; // error code for insufficient elements
    }

    double min_val = numbers[0];
    double max_val = numbers[0];

    // Find minimum and maximum values
    for (int i = 1; i < len; ++i) {
        if (numbers[i] < min_val) min_val = numbers[i];
        if (numbers[i] > max_val) max_val = numbers[i];
    }

    // If all numbers are equal, rescaling is undefined
    if (min_val == max_val) {
        return -2; // error code for division by zero
    }

    double denom = max_val - min_val;

    // Compute rescaled values
    for (int i = 0; i < len; ++i) {
        out[i] = (numbers[i] - min_val) / denom;
    }

    return 0; // success
}

// Helper function to compute absolute difference between two doubles
double abs_diff(double a, double b) {
    return (a > b) ? (a - b) : (b - a);
}

// Test suite replicating the original Python tests
void run_tests(void) {
    // Test 1
    double arr1[2] = {2.0, 49.9};
    double out1[2];
    assert(rescale_to_unit(arr1, 2, out1) == 0);
    double expected1[2] = {0.0, 1.0};
    for (int i = 0; i < 2; ++i) {
        assert(abs_diff(out1[i], expected1[i]) < 1e-6);
    }

    // Test 2
    double arr2[2] = {100.0, 49.9};
    double out2[2];
    assert(rescale_to_unit(arr2, 2, out2) == 0);
    double expected2[2] = {1.0, 0.0};
    for (int i = 0; i < 2; ++i) {
        assert(abs_diff(out2[i], expected2[i]) < 1e-6);
    }

    // Test 3
    double arr3[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double out3[5];
    assert(rescale_to_unit(arr3, 5, out3) == 0);
    double expected3[5] = {0.0, 0.25, 0.5, 0.75, 1.0};
    for (int i = 0; i < 5; ++i) {
        assert(abs_diff(out3[i], expected3[i]) < 1e-6);
    }

    // Test 4
    double arr4[5] = {2.0, 1.0, 5.0, 3.0, 4.0};
    double out4[5];
    assert(rescale_to_unit(arr4, 5, out4) == 0);
    double expected4[5] = {0.25, 0.0, 1.0, 0.5, 0.75};
    for (int i = 0; i < 5; ++i) {
        assert(abs_diff(out4[i], expected4[i]) < 1e-6);
    }

    // Test 5
    double arr5[5] = {12.0, 11.0, 15.0, 13.0, 14.0};
    double out5[5];
    assert(rescale_to_unit(arr5, 5, out5) == 0);
    double expected5[5] = {0.25, 0.0, 1.0, 0.5, 0.75};
    for (int i = 0; i < 5; ++i) {
        assert(abs_diff(out5[i], expected5[i]) < 1e-6);
    }
}

// Entry point to execute tests
int main(void) {
    run_tests();
    return 0;
}