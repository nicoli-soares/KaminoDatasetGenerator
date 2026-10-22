typedef struct {
    char data[1024];
    size_t length;
} StringGroup;

int parse_nested_parens_c(const char *input, int *result, size_t size) {
    StringGroup groups;
    strcpy(groups.data, input);
    groups.length = strlen(input);

    char *token = strtok(groups.data, " ");
    int groupIndex = 0;

    while (token != NULL && groupIndex < size) {
        int depth = 0;
        int max_depth = 0;
        size_t len = strlen(token);

        for (size_t i = 0; i < len; i++) {
            if (token[i] == '(') {
                depth++;
                if (depth > max_depth) {
                    max_depth = depth;
                }
            } else if (token[i] == ')') {
                depth--;
            }
        }

        result[groupIndex++] = max_depth;
        token = strtok(NULL, " ");
    }

    return 0;
}

void test_case_1() {
    int result[4];
    parse_nested_parens_c("(()()) ((())) () ((())()())", result, sizeof(result)/sizeof(result[0]));
    assert(result[0] == 2);
    assert(result[1] == 3);
    assert(result[2] == 1);
    assert(result[3] == 3);
}

void test_case_2() {
    int result[4];
    parse_nested_parens_c("() (()) ((())) (((())))", result, sizeof(result)/sizeof(result[0]));
    assert(result[0] == 1);
    assert(result[1] == 2);
    assert(result[2] == 3);
    assert(result[3] == 4);
}

void test_case_3() {
    int result[1];
    parse_nested_parens_c("(()(())((())))", result, sizeof(result)/sizeof(result[0]));
    assert(result[0] == 4);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}