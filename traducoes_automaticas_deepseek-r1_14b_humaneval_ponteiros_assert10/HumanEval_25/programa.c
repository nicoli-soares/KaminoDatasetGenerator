int factorize_c(int n, int *factors, size_t size) {
    int count = 0;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            if (count >= size) {
                return -1;
            }
            factors[count++] = i;
            n /= i;
            while (n % i == 0) {
                if (count >= size) {
                    return -1;
                }
                factors[count++] = i;
                n /= i;
            }
        }
        i++;
    }
    if (n > 1) {
        if (count >= size) {
            return -1;
        }
        factors[count++] = n;
    }
    return count;
}

void test_factorize_with_8() {
    int factors[1000];
    int count = factorize_c(8, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 3);
    assert(factors[0] == 2 && factors[1] == 2 && factors[2] == 2);
}

void test_factorize_with_2() {
    int factors[1000];
    int count = factorize_c(2, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 1 && factors[0] == 2);
}

void test_factorize_with_4() {
    int factors[1000];
    int count = factorize_c(4, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 2 && factors[0] == 2 && factors[1] == 2);
}

void test_factorize_with_3_19() {
    int factors[1000];
    int count = factorize_c(57, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 2 && factors[0] == 3 && factors[1] == 19);
}

void test_factorize_with_3_19_3_19() {
    int factors[1000];
    int count = factorize_c(3*19*3*19, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 4);
    assert(factors[0] == 3 && factors[1] == 3 && factors[2] == 19 && factors[3] == 19);
}

void test_factorize_with_3_19_19_19() {
    int factors[1000];
    int count = factorize_c(3*19*19*19, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 4);
    assert(factors[0] == 3 && factors[1] == 19 && factors[2] == 19 && factors[3] == 19);
}

void test_factorize_with_3_2_3() {
    int factors[1000];
    int count = factorize_c(3*2*3, factors, sizeof(factors)/sizeof(factors[0]));
    assert(count == 3);
    assert(factors[0] == 2 && factors[1] == 3 && factors[2] == 3);
}

int main() {
    test_factorize_with_8();
    test_factorize_with_2();
    test_factorize_with_4();
    test_factorize_with_3_19();
    test_factorize_with_3_19_3_19();
    test_factorize_with_3_19_19_19();
    test_factorize_with_3_2_3();
    return 0;
}