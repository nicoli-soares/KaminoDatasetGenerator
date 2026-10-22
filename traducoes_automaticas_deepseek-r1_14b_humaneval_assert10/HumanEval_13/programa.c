typedef struct {
    int a;
    int b;
} ParesInteiros;

int greatest_common_divisor_c(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void testar_maior_divisor_comum() {
    assert(greatest_common_divisor_c(3, 7) == 1);
    assert(greatest_common_divisor_c(10, 15) == 5);
    assert(greatest_common_divisor_c(49, 14) == 7);
    assert(greatest_common_divisor_c(144, 60) == 12);
}

int main() {
    testar_maior_divisor_comum();
    return 0;
}