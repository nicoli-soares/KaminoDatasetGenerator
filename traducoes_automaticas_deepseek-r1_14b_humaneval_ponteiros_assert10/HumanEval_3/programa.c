typedef struct {
    int op;
} Operacao;

int below_zero_c(const int operations[], size_t n) {
    int balance = 0;

    for (size_t i = 0; i < n; i++) {
        balance += operations[i];
        if (balance < 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int test1[] = {};
    assert(below_zero_c(test1, 0) == 0);

    int test2[] = {1, 2, -3, 1, 2, -3};
    assert(below_zero_c(test2, 6) == 0);

    int test3[] = {1, 2, -4, 5, 6};
    assert(below_zero_c(test3, 5) == 1);

    int test4[] = {1, -1, 2, -2, 5, -5, 4, -4};
    assert(below_zero_c(test4, 8) == 0);

    int test5[] = {1, -1, 2, -2, 5, -5, 4, -5};
    assert(below_zero_c(test5, 8) == 1);

    int test6[] = {1, -2, 2, -2, 5, -5, 4, -4};
    assert(below_zero_c(test6, 8) == 1);

    return 0;
}