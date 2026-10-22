typedef struct {
    char *str;
    int depth;
} GroupInfo;

int calculate_max_depth(char *s) {
    int depth = 0, max_depth = 0;
    for (char *c = s; *c != '\0'; c++) {
        if (*c == '(') {
            depth++;
            if (depth > max_depth) {
                max_depth = depth;
            }
        } else if (*c == ')') {
            depth--;
        }
    }
    return max_depth;
}

char** split_groups(char *str, int *count) {
    char **tokens = NULL;
    char *current_str = str;
    size_t current_count = 0;
    
    while (1) {
        char *token = strtok(current_str, " ");
        if (token == NULL) {
            break;
        }
        
        tokens = realloc(tokens, (current_count + 1) * sizeof(char*));
        tokens[current_count] = strdup(token);
        
        current_count++;
        current_str = NULL;
    }
    
    *count = current_count;
    return tokens;
}

int* parse_nested_parens(char *paren_string) {
    int count = 0;
    char **groups = split_groups(paren_string, &count);
    int *result = (int *)malloc(count * sizeof(int));
    
    for (int i = 0; i < count; i++) {
        result[i] = calculate_max_depth(groups[i]);
    }
    
    for (int i = 0; i < count; i++) {
        free(groups[i]);
    }
    free(groups);
    return result;
}

void test_case_1() {
    char input[] = "(()()) ((())) () ((())()())";
    int expected[] = {2, 3, 1, 3};
    int *result = parse_nested_parens(input);
    for (int i = 0; i < 4; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

void test_case_2() {
    char input[] = "() (()) ((())) (((())))";
    int expected[] = {1, 2, 3, 4};
    int *result = parse_nested_parens(input);
    for (int i = 0; i < 4; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

int main() {
    test_case_1();
    test_case_2();
    return 0;
}