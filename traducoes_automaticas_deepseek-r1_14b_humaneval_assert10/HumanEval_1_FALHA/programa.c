typedef struct {
    char **data;
    int size;
} StringList;

StringList separate_paren_groups_c(const char *input) {
    StringList result = {0};
    char current_string[256];
    int current_depth = 0;
    int string_length = 0;
    const char *current_pos = input;

    while (*current_pos != '\0') {
        // Skip leading spaces
        while (*current_pos == ' ') {
            current_pos++;
        }

        if (*current_pos == '\0') {
            break;
        }

        // Start of a new group
        current_depth = 0;
        string_length = 0;

        do {
            char c = *current_pos++;
            if (c == ' ') {
                continue; // Ignore spaces within the group
            }
            if (c == '(') {
                current_depth++;
            } else if (c == ')') {
                current_depth--;
            }
            current_string[string_length++] = c;
            current_string[string_length] = '\0';  // Ensure null-termination

            // Check if the group is closed
            if (current_depth == 0) {
                break;
            }
        } while (*current_pos != ' ' && *current_pos != '\0');

        if (current_depth == 0) {
            char *new_string = (char *)malloc(string_length + 1);
            memcpy(new_string, current_string, string_length + 1);
            result.data = (char **)realloc(result.data, sizeof(char *) * (result.size + 1));
            result.data[result.size++] = new_string;
            string_length = 0;
            memset(current_string, 0, sizeof(current_string));  // Reset current_string
        }
    }

    return result;
}

void test_case_1() {
    StringList output = separate_paren_groups_c("(()()) ((())) () ((())()())");
    assert(output.size == 4);
    assert(strcmp(output.data[0], "(()())") == 0);
    assert(strcmp(output.data[1], "((()))") == 0);
    assert(strcmp(output.data[2], "()") == 0);
    assert(strcmp(output.data[3], "((())()())") == 0);
}

void test_case_2() {
    StringList output = separate_paren_groups_c("() (()) ((())) (((())))");
    assert(output.size == 4);
    assert(strcmp(output.data[0], "()") == 0);
    assert(strcmp(output.data[1], "(())") == 0);
    assert(strcmp(output.data[2], "((()))") == 0);
    assert(strcmp(output.data[3], "((((())))") == 0);
}

void test_case_3() {
    StringList output = separate_paren_groups_c("(()(())((())))");
    assert(output.size == 1);
    assert(strcmp(output.data[0], "(()(())((())))") == 0);
}

void test_case_4() {
    StringList output = separate_paren_groups_c("( ) (( )) (( )( ))");
    assert(output.size == 3);
    assert(strcmp(output.data[0], "()") == 0);
    assert(strcmp(output.data[1], "(())") == 0);
    assert(strcmp(output.data[2], "(()())") == 0);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}