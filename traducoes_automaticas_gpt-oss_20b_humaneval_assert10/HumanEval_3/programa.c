#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define false 0
#define true 1

int below_zero(const int *operations, int len) {
    int balance = 0;
    for (int i = 0; i < len; ++i) {
        balance += operations[i];
        if (balance < 0) {
            return true;
        }
    }
    return false;
}

void check_below_zero(void) {
    // Test 1: empty array
    assert(below_zero(NULL, 0) == false);

    // Test 2
    int ops2[] = {1, 2, -3, 1, 2, -3};
    assert(below_zero(ops2, 6) == false);

    // Test 3
    int ops3[] = {1, 2, -4, 5, 6};
    assert(below_zero(ops3, 5) == true);

    // Test 4
    int ops4[] = {1, -1, 2, -2, 5, -5, 4, -4};
    assert(below_zero(ops4, 8) == false);

    // Test 5
    int ops5[] = {1, -1, 2, -2, 5, -5, 4, -5};
    assert(below_zero(ops5, 8) == true);

    // Test 6
    int ops6[] = {1, -2, 2, -2, 5, -5, 4, -4};
    assert(below_zero(ops6, 8) == true);
}

int main(void) {
    check_below_zero();
    return 0;
}