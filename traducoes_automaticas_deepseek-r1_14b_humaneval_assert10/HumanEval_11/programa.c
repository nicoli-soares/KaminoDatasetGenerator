typedef struct {
    char chave;
    char valor;
} ChaveValor;

char* string_xor(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int min_len = len_a < len_b ? len_a : len_b;
    char* result = malloc(min_len + 1);
    result[min_len] = '\0';
    
    for (int i = 0; i < min_len; i++) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    
    return result;
}

void test_case_1() {
    char* result = string_xor("111000", "101010");
    assert(strcmp(result, "010010") == 0);
    free(result);
}

void test_case_2() {
    char* result = string_xor("1", "1");
    assert(strcmp(result, "0") == 0);
    free(result);
}

void test_case_3() {
    char* result = string_xor("0101", "0000");
    assert(strcmp(result, "0101") == 0);
    free(result);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}