#include <assert.h>

typedef struct {
    int value;
} Operation;

int below_zero_c(Operation* operations, int n) {
    int balance = 0;

    for (int i = 0; i < n; i++) {
        balance += operations[i].value;
        if (balance < 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    Operation ops1[] = {1, 2, -3, 1, 2, -3};
    Operation ops2[] = {1, 2, -4, 5, 6};
    Operation ops3[] = {1, -1, 2, -2, 5, -5, 4, -4};
    Operation ops4[] = {1, -1, 2, -2, 5, -5, 4, -5};
    Operation ops5[] = {1, -2, 2, -2, 5, -5, 4, -4};

    assert(below_zero_c(NULL, 0) == 0);
    assert(below_zero_c(ops1, 6) == 0);
    assert(below_zero_c(ops2, 5) == 1);
    assert(below_zero_c(ops3, 8) == 0);
    assert(below_zero_c(ops4, 8) == 1);
    assert(below_zero_c(ops5, 8) == 1);

    return 0;
}