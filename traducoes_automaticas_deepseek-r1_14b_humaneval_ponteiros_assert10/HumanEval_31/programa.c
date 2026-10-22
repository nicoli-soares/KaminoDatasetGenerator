int is_prime_c(int n) {
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (int k = 3; k <= sqrt(n); k += 2) {
        if (n % k == 0) {
            return 0;
        }
    }
    return 1;
}

int check_c(int candidate(int n)) {
    assert(candidate(6) == 0);
    assert(candidate(101) == 1);
    assert(candidate(11) == 1);
    assert(candidate(13441) == 1);
    assert(candidate(61) == 1);
    assert(candidate(4) == 0);
    assert(candidate(1) == 0);
    assert(candidate(5) == 1);
    assert(candidate(17) == 1);
    assert(candidate(5 * 17) == 0);
    assert(candidate(11 * 7) == 0);
    assert(candidate(13441 * 19) == 0);
    return 0;
}

int main() {
    check_c(is_prime_c);
    return 0;
}