#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int fizz_buzz(int n){
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (i % 11 == 0 || i % 13 == 0){
            int temp = i;
            /* handle 0 explicitly – its digit is 0, not 7 */
            if (temp == 0){
                /* nothing to add */
            } else {
                while (temp > 0){
                    int digit = temp % 10;
                    if (digit == 7) ans++;
                    temp /= 10;
                }
            }
        }
    }
    return ans;
}

int main(void){
    /* Tests translated from the original Python test suite */
    assert(fizz_buzz(50) == 0);
    assert(fizz_buzz(78) == 2);
    assert(fizz_buzz(79) == 3);
    assert(fizz_buzz(100) == 3);
    assert(fizz_buzz(200) == 6);
    assert(fizz_buzz(4000) == 192);
    assert(fizz_buzz(10000) == 639);
    assert(fizz_buzz(100000) == 8026);
    return 0;
}