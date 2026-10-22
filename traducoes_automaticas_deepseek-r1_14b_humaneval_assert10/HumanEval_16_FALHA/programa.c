#include <assert.h>
#include <stdbool.h>

int count_distinct_characters(const char* string) {
    bool letters[26] = {0};
    int count = 0;
    for (; *string != '\0'; string++) {
        char c = tolower(*string);
        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            if (!letters[index]) {
                letters[index] = 1;
                count++;
            }
        }
    }
    return count;
}

void test_case1() {
    assert(count_distinct_characters("") == 0);
}

void test_case2() {
    assert(count_distinct_characters("abcde") == 5);
}

void test_case3() {
    assert(count_distinct_characters("abcde cade CADE") == 5);
}

void test_case4() {
    assert(count_distinct_characters("aaaaAAAAaaaa") == 1);
}

void test_case5() {
    assert(count_distinct_characters("Jerry jERRY JeRRRY") == 5);
}

int main() {
    test_case1();
    test_case2();
    test_case3();
    test_case4();
    test_case5();
    return 0;
}