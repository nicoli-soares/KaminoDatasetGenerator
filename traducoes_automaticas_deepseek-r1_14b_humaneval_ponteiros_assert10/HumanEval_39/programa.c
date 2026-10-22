#include <assert.h>

int is_prime_c(long long p) {
    if (p < 2) return 0;
    for (long long i = 2; i <= (p / i); i++) {
        if (p % i == 0) return 0;
    }
    return 1;
}

long long prime_fib_c(int n) {
    long long a = 0, b = 1, c = 0;
    int count = 0;
    
    while (1) {
        c = a + b;
        if (is_prime_c(c)) {
            count++;
            if (count == n) return c;
        }
        a = b;
        b = c;
    }
}

void check_c() {
    assert(prime_fib_c(1) == 2);
    assert(prime_fib_c(2) == 3);
    assert(prime_fib_c(3) == 5);
    assert(prime_fib_c(4) == 13);
    assert(prime_fib_c(5) == 89);
    assert(prime_fib_c(6) == 233);
    assert(prime_fib_c(7) == 1597);
    assert(prime_fib_c(8) == 28657);
    assert(prime_fib_c(9) == 514229);
    assert(prime_fib_c(10) == 433494437);
}

int main() {
    check_c();
    return 0;
}