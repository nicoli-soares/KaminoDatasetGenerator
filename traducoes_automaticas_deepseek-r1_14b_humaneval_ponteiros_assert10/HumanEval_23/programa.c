int strlen_c(const char *string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

void test_strlen() {
    assert(strlen_c("") == 0);
    assert(strlen_c("x") == 1);
    assert(strlen_c("asdasnakj") == 9);
}

int main() {
    test_strlen();
    return 0;
}