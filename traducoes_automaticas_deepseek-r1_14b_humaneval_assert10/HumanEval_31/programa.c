int is_prime_c(int n) {
    if (n < 2) {
        return 0;
    }
    for (int k = 2; k < n; k++) {
        if (n % k == 0) {
            return 0;
        }
    }
    return 1;
}

void test_is_prime_c() {
    assert(is_prime_c(6) == 0);
    assert(is_prime_c(101) == 1);
    assert(is_prime_c(11) == 1);
    assert(is_prime_c(13441) == 1);
    assert(is_prime_c(61) == 1);
    assert(is_prime_c(4) == 0);
    assert(is_prime_c(1) == 0);
    assert(is_prime_c(5) == 1);
    assert(is_prime_c(17) == 1);
    assert(is_prime_c(5 * 17) == 0);
    assert(is_prime_c(11 * 7) == 0);
    assert(is_prime_c(13441 * 19) == 0);
}

int main() {
    test_is_prime_c();
    return 0;
}