typedef struct {
    const char *str;
    int length;
} TestString;

TestString test_strings[] = {
    {"", 0},
    {"x", 1},
    {"asdasnakj", 9}
};

int strlen_c(const char *str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

void test_case1() {
    assert(strlen_c("") == 0);
}

void test_case2() {
    assert(strlen_c("x") == 1);
}

void test_case3() {
    assert(strlen_c("asdasnakj") == 9);
}

int main() {
    test_case1();
    test_case2();
    test_case3();
    return 0;
}