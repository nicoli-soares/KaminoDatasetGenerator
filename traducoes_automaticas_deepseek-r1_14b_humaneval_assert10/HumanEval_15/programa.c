char* string_sequence_c(int n) {
    if (n < 0) {
        return ""; // Invalid input
    }
    char buffer[1024];
    int pos = 0;
    for (int i = 0; i <= n; i++) {
        if (i > 0) {
            pos += snprintf(buffer + pos, sizeof(buffer) - pos, " ");
        }
        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "%d", i);
    }
    return strdup(buffer);
}

void check(char* (*candidate)(int)) {
    assert(strcmp(candidate(0), "0") == 0);
    assert(strcmp(candidate(3), "0 1 2 3") == 0);
    assert(strcmp(candidate(10), "0 1 2 3 4 5 6 7 8 9 10") == 0);
}

int main() {
    check(string_sequence_c);
    return 0;
}