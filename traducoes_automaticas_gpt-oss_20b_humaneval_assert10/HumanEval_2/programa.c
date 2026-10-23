#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    double value;
} ResultWrapper;

double truncate_number(double number) {
    // Works only for positive numbers, as per the original spec.
    long long int_part = (long long)number;
    return number - (double)int_part;
}

double abs_double(double x) {
    return x < 0.0 ? -x : x;
}

/* Test functions */
void test_truncate_number() {
    assert(truncate_number(3.5) == 0.5);
    assert(abs_double(truncate_number(1.33) - 0.33) < 1e-6);
    assert(abs_double(truncate_number(123.456) - 0.456) < 1e-6);
}

/* Main to run tests */
int main(void) {
    test_truncate_number();
    return 0;
}