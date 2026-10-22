void string_sequence_c(int n, char *buffer, size_t buffer_size) {
    if (n < 0) {
        snprintf(buffer, buffer_size, "Erro: n nao pode ser negativo");
        return;
    }
    
    int pos = 0;
    for (int i = 0; i <= n; i++) {
        if (i > 0) {
            // Escreve um espaço
            if (pos >= buffer_size) {
                snprintf(buffer, buffer_size, "Buffer insuficiente");
                return;
            }
            buffer[pos++] = ' ';
        }
        // Escreve o numero
        if (pos >= buffer_size) {
            snprintf(buffer, buffer_size, "Buffer insuficiente");
            return;
        }
        snprintf(buffer + pos, buffer_size - pos, "%d", i);
        pos += strlen(buffer + pos);
    }
    buffer[pos] = '\0';
}

void test_string_sequence_c() {
    // Test 1: n = 0
    char buffer[1024];
    string_sequence_c(0, buffer, sizeof(buffer));
    assert(strcmp(buffer, "0") == 0);

    // Test 2: n = 3
    string_sequence_c(3, buffer, sizeof(buffer));
    assert(strcmp(buffer, "0 1 2 3") == 0);

    // Test 3: n = 10
    string_sequence_c(10, buffer, sizeof(buffer));
    assert(strcmp(buffer, "0 1 2 3 4 5 6 7 8 9 10") == 0);
}

int main() {
    test_string_sequence_c();
    return 0;
}