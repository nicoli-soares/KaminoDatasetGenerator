typedef struct {
    char group[256];
    int max_depth;
} GroupResult;

int* parse_nested_parens_c(char *input, int input_len, int *output_len) {
    char *current_group = input;
    int groups = 0;
    int depth = 0;
    int max_depth = 0;
    int max_group_depth = 0;
    int *results = malloc(1000 * sizeof(int));  // Allocate space for 1000 groups

    if (!results) {
        return NULL;
    }

    while (*current_group) {
        if (*current_group == ' ') {
            results[groups] = max_depth;
            groups++;
            current_group++;
            depth = 0;
            max_depth = 0;
        } else if (*current_group == '(') {
            depth++;
            if (depth > max_depth) {
                max_depth = depth;
            }
        } else if (*current_group == ')') {
            depth--;
        }
        current_group++;
    }

    *output_len = groups;
    return results;
}

void test1() {
    char input[] = "(()()) ((())) () ((())()())";
    int len = sizeof(input);
    int output_len = 0;
    int *result = parse_nested_parens_c(input, len, &output_len);
    
    if (result) {
        assert(result[0] == 2);
        assert(result[1] == 3);
        assert(result[2] == 1);
        assert(result[3] == 3);
        free(result);
    }
}

void test2() {
    char input[] = "() (()) ((())) (((())))";
    int len = sizeof(input);
    int output_len = 0;
    int *result = parse_nested_parens_c(input, len, &output_len);
    
    if (result) {
        assert(result[0] == 1);
        assert(result[1] == 2);
        assert(result[2] == 3);
        assert(result[3] == 4);
        free(result);
    }
}

void test3() {
    char input[] = "(()(())((())))";
    int len = sizeof(input);
    int output_len = 0;
    int *result = parse_nested_parens_c(input, len, &output_len);
    
    if (result) {
        assert(result[0] == 4);
        free(result);
    }
}

int main() {
    test1();
    test2();
    test3();
}