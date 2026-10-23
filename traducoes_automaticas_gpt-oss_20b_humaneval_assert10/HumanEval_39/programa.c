#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define true 1
#define false 0

/* Helper function to check primality */
int is_prime(unsigned long long p) {
    if (p < 2) return false;
    for (unsigned long long k = 2; k * k <= p; ++k) {
        if (p % k == 0) return false;
    }
    return true;
}

/* Main function: returns the n-th prime Fibonacci number */
unsigned long long prime_fib(unsigned int n) {
    unsigned long long a = 0, b = 1, c;
    while (1) {
        c = a + b;
        if (is_prime(c)) {
            if (n == 1) return c;
            --n;
        }
        a = b;
        b = c;
    }
}

/* Test function */
void test_prime_fib(void) {
    assert(prime_fib(1) == (unsigned long long)2);
    assert(prime_fib(2) == (unsigned long long)3);
    assert(prime_fib(3) == (unsigned long long)5);
    assert(prime_fib(4) == (unsigned long long)13);
    assert(prime_fib(5) == (unsigned long long)89);
    assert(prime_fib(6) == (unsigned long long)233);
    assert(prime_fib(7) == (unsigned long long)1597);
    assert(prime_fib(8) == (unsigned long long)28657);
    assert(prime_fib(9) == (unsigned long long)514229);
    assert(prime_fib(10) == (unsigned long long)433494437);
}

/* Main entry point */
int main(void) {
    test_prime_fib();
    return 0;
}