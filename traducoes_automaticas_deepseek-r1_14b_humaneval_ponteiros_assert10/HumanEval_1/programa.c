typedef struct {
    char text[256];
} GroupString;

int separate_paren_groups_c(const char* paren_string, GroupString result_groups[100], int* group_count) {
    int current_depth = 0;
    char current_str[256];
    int str_len = 0;

    char* ptr = (char*)paren_string;
    while (*ptr != '\0') {
        char c = *ptr++;
        if (c == ' ') continue;

        if (c == '(') {
            current_depth++;
            current_str[str_len++] = '(';
        } else if (c == ')') {
            if (current_depth == 0) {
                continue;
            }
            current_depth--;
            current_str[str_len++] = ')';

            if (current_depth == 0) {
                current_str[str_len] = '\0';
                if (*group_count >= 100) {
                    return -1;
                }
                strcpy(result_groups[*group_count].text, current_str);
                (*group_count)++;
                str_len = 0;
            }
        }
    }
    return 0;
}

void test_case1() {
    const char* input = "(()()) ((())) () ((())()())";
    GroupString result_groups[100];
    int group_count = 0;

    separate_paren_groups_c(input, result_groups, &group_count);
    assert(group_count == 4);
    assert(strcmp(result_groups[0].text, "(()())") == 0);
    assert(strcmp(result_groups[1].text, "((()))") == 0);
    assert(strcmp(result_groups[2].text, "()") == 0);
    assert(strcmp(result_groups[3].text, "((())()())") == 0);
}

void test_case2() {
    const char* input = "() (()) ((())) (((())))";
    GroupString result_groups[100];
    int group_count = 0;

    separate_paren_groups_c(input, result_groups, &group_count);
    assert(group_count == 4);
    assert(strcmp(result_groups[0].text, "()") == 0);
    assert(strcmp(result_groups[1].text, "(())") == 0);
    assert(strcmp(result_groups[2].text, "((()))") == 0);
    assert(strcmp(result_groups[3].text, "(((())))") == 0);
}

void test_case3() {
    const char* input = "(()(())((())))";
    GroupString result_groups[100];
    int group_count = 0;

    separate_paren_groups_c(input, result_groups, &group_count);
    assert(group_count == 1);
    assert(strcmp(result_groups[0].text, "(()(())((())))") == 0);
}

void test_case4() {
    const char* input = "( ) (( )) (( )( ))";
    GroupString result_groups[100];
    int group_count = 0;

    separate_paren_groups_c(input, result_groups, &group_count);
    assert(group_count == 3);
    assert(strcmp(result_groups[0].text, "()") == 0);
    assert(strcmp(result_groups[1].text, "(())") == 0);
    assert(strcmp(result_groups[2].text, "(()())") == 0);
}

int main() {
    test_case1();
    test_case2();
    test_case3();
    test_case4();
    return 0;
}