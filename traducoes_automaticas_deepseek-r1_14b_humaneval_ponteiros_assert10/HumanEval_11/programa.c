typedef struct {
    char xor_result[1024];  // Buffer para armazenar o resultado do XOR
} XorResult;

int string_xor_c(const char *a, int len_a, const char *b, int len_b, char *result) {
    // Função auxiliar para calcular XOR de dois caracteres
    char xor_char(char x, char y) {
        if (x == y) {
            return '0';
        } else {
            return '1';
        }
    }

    int min_len = (len_a < len_b) ? len_a : len_b;
    int result_len = 0;

    for (int i = 0; i < min_len; i++) {
        result[result_len++] = xor_char(a[i], b[i]);
    }

    result[result_len] = '\0';  // Terminar a string
    return result_len;  // Retorna o tamanho do resultado
}

void test_case_1() {
    char a[] = "111000";
    char b[] = "101010";
    char result[1024];
    assert(string_xor_c(a, 6, b, 6, result) == 6);
    assert(strcmp(result, "010010") == 0);
}

void test_case_2() {
    char a[] = "1";
    char b[] = "1";
    char result[1024];
    assert(string_xor_c(a, 1, b, 1, result) == 1);
    assert(strcmp(result, "0") == 0);
}

void test_case_3() {
    char a[] = "0101";
    char b[] = "0000";
    char result[1024];
    assert(string_xor_c(a, 4, b, 4, result) == 4);
    assert(strcmp(result, "0101") == 0);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}