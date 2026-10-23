#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int greatest_common_divisor(int a, int b){
    while(b){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void test_greatest_common_divisor(void){
    assert(greatest_common_divisor(3,7) == 1);
    assert(greatest_common_divisor(10,15) == 5);
    assert(greatest_common_divisor(49,14) == 7);
    assert(greatest_common_divisor(144,60) == 12);
}

int main(void){
    test_greatest_common_divisor();
    return 0;
}