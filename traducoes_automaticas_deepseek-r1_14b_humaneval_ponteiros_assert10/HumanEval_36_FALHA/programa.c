int fizz_buzz_c(int n) {
    if (n <= 0) return 0;
    
    char *buffer = NULL;
    size_t buffer_size = 1; // Inicialização com tamanho 1 para evitar NULL
    size_t current_length = 0;
    
    for (int i = 0; i < n; i++) {
        if (i % 11 == 0 || i % 13 == 0) {
            int comma = current_length ? 1 : 0;
            int needed = snprintf(buffer, buffer_size, "%s%d", (comma ? "," : ""), i);
            
            if (needed >= buffer_size) {
                buffer_size = needed + 1;
                buffer = realloc(buffer, buffer_size);
                if (buffer == NULL) {
                    free(buffer);
                    return -1;
                }
            }
            
            current_length += needed - comma;
        }
    }
    
    int count = 0;
    for (size_t i = 0; i < current_length; i++) {
        if (buffer[i] == '7') {
            count++;
        }
    }
    
    free(buffer);
    return count;
}

void test_fizz_buzz_c() {
    assert(fizz_buzz_c(50) == 0);
    assert(fizz_buzz_c(78) == 2);
    assert(fizz_buzz_c(79) == 3);
    assert(fizz_buzz_c(100) == 3);
    assert(fizz_buzz_c(200) == 6);
    assert(fizz_buzz_c(4000) == 192);
    assert(fizz_buzz_c(10000) == 639);
    assert(fizz_buzz_c(100000) == 8026);
}

int main() {
    test_fizz_buzz_c();
    return 0;
}