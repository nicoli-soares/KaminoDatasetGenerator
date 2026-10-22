/* Função principal */
int largest_divisor_c(int n) {
    for (int i = n - 1; i >= 1; i--) {
        if (n % i == 0) {
            return i;
        }
    }
    return 1; /* Se n for primo, retorna 1 */
}

/* Testes */
void test_largest_divisor_c() {
    assert(largest_divisor_c(3) == 1);
    assert(largest_divisor_c(7) == 1);
    assert(largest_divisor_c(10) == 5);
    assert(largest_divisor_c(100) == 50);
    assert(largest_divisor_c(49) == 7);
}

/* Função main que executa os testes */
int main() {
    test_largest_divisor_c();
    return 0;
}