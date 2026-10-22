typedef struct {
    const char* str;
    int len;
} StrInfo;

int how_many_times(const char* string, const char* substring) {
    int times = 0;
    int len_string = strlen(string);
    int len_substring = strlen(substring);
    
    if (len_substring == 0 || len_string < len_substring) {
        return 0;
    }
    
    for (int i = 0; i <= len_string - len_substring; i++) {
        if (strncmp(string + i, substring, len_substring) == 0) {
            times++;
        }
    }
    
    return times;
}

void test_case_1() {
    assert(how_many_times("", "x") == 0);
}

void test_case_2() {
    assert(how_many_times("xyxyxyx", "x") == 4);
}

void test_case_3() {
    assert(how_many_times("cacacacac", "cac") == 4);
}

void test_case_4() {
    assert(how_many_times("john doe", "john") == 1);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}