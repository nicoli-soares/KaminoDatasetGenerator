#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int largest_divisor(int n) {
    // For n <= 1 the behavior is undefined in the original Python code.
    // We return 1 as a safe default.
    if (n <= 1) {
        return 1;
    }
    for (int i = n - 1; i > 0; --i) {
        if (n % i == 0) {
            return i;
        }
    }
    // Should never reach here because 1 always divides n.
    return 1;
}

void test_largest_divisor(void) {
    assert(largest_divisor(3) == 1);
    assert(largest_divisor(7) == 1);
    assert(largest_divisor(10) == 5);
    assert(largest_divisor(100) == 50);
    assert(largest_divisor(49) == 7);
}

int main(void) {
    test_largest_divisor();
    return 0;
}