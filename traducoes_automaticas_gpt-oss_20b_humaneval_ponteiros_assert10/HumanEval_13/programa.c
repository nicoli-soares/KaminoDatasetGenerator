#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int greatest_common_divisor(int a, int b)
{
    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void run_tests()
{
    /* Test cases from the original Python doctest suite */
    assert(greatest_common_divisor(3, 7) == 1);
    assert(greatest_common_divisor(10, 15) == 5);
    assert(greatest_common_divisor(49, 14) == 7);
    assert(greatest_common_divisor(144, 60) == 12);
}

int main()
{
    run_tests();
    return 0;
}