#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

static inline double fabs_custom(double x) {
    return x < 0.0 ? -x : x;
}

double mean_absolute_deviation(const double *numbers, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += numbers[i];
    }
    double mean = sum / n;
    double total = 0.0;
    for (int i = 0; i < n; ++i) {
        double diff = numbers[i] - mean;
        total += fabs_custom(diff);
    }
    return total / n;
}

void test1(void) {
    double data[] = {1.0, 2.0, 3.0};
    double result = mean_absolute_deviation(data, 3);
    assert(fabs_custom(result - (2.0/3.0)) < 1e-6);
}

void test2(void) {
    double data[] = {1.0, 2.0, 3.0, 4.0};
    double result = mean_absolute_deviation(data, 4);
    assert(fabs_custom(result - 1.0) < 1e-6);
}

void test3(void) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = mean_absolute_deviation(data, 5);
    assert(fabs_custom(result - (6.0/5.0)) < 1e-6);
}

int main(void) {
    test1();
    test2();
    test3();
    return 0;
}