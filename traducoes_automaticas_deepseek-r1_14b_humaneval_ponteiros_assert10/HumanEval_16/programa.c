typedef struct {
    char c;
    int present;
} CharacterPresence;

int count_distinct_characters_c(const char *string) {
    CharacterPresence characters[256];  // Assuming extended ASCII
    memset(characters, 0, sizeof(characters));
    
    while (*string != '\0') {
        char lower_char = tolower(*string);
        characters[(unsigned char)lower_char].present = 1;
        string++;
    }
    
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (characters[i].present == 1) {
            count++;
        }
    }
    return count;
}

void test_case_1() {
    assert(count_distinct_characters_c("") == 0);
}

void test_case_2() {
    assert(count_distinct_characters_c("abcde") == 5);
}

void test_case_3() {
    assert(count_distinct_characters_c("abcdeCADE") == 5);
}

void test_case_4() {
    assert(count_distinct_characters_c("aaaaAAAAaaaa") == 1);
}

void test_case_5() {
    assert(count_distinct_characters_c("Jerry jERRY JeRRRY") == 5);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    return 0;
}