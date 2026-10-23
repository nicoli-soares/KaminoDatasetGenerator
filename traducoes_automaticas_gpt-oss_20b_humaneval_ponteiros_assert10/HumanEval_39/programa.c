#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef long long int int64;

// Helper to determine if a number is prime.
// Uses trial division up to sqrt(p).
static int is_prime(int64 p) {
    if (p < 2) {
        return 0;
    }
    int64 limit = (int64)sqrt((double)p);
    if (limit > p - 1) {
        limit = p - 1;
    }
    for (int64 k = 2; k <= limit; ++k) {
        if (p % k == 0) {
            return 0;
        }
    }
    return 1;
}

// Returns the n-th Fibonacci number that is also prime.
// n must be >= 1.
int64 prime_fib(int n) {
    int64 a = 0;
    int64 b = 1;
    while (1) {
        int64 next = a + b;
        a = b;
        b = next;
        if (is_prime(b)) {
            n--;
            if (n == 0) {
                return b;
            }
        }
    }
}

// Test suite replicating the original Python tests.
static void check() {
    assert(prime_fib(1) == 2);
    assert(prime_fib(2) == 3);
    assert(prime_fib(3) == 5);
    assert(prime_fib(4) == 13);
    assert(prime_fib(5) == 89);
    assert(prime_fib(6) == 233);
    assert(prime_fib(7) == 1597);
    assert(prime_fib(8) == 28657);
    assert(prime_fib(9) == 514229);
    assert(prime_fib(10) == 433494437);
}

int main() {
    check();
    return 0;
}