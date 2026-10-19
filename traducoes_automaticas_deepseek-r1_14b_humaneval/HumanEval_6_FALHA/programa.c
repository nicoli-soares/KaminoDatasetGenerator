typedef struct {
    char *str;
    int max_depth;
} ParenGroup;

int parse_paren_group_c(char *s) {
    int depth = 0;
    int max_depth = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            depth++;
            if (depth > max_depth) {
                max_depth = depth;
            }
        } else if (s[i] == ')') {
            depth--;
        }
    }
    return max_depth;
}

int *parse_nested_parens_c(char *paren_string, int *return_size) {
    if (paren_string == NULL || *paren_string == '\0') {
        *return_size = 0;
        return NULL;
    }

    char *current = paren_string;
    char *original = paren_string;
    char *end = NULL;
    int group_count = 0;
    int token_count = 0;

    // First pass: count tokens, skipping empty strings
    while ((end = strstr(current, " ")) != NULL) {
        current = end + 1;
        if (current[0] != '\0') {
            token_count++;
        }
    }
    if (original[strlen(original) - 1] != ' ') {
        token_count++;
    }

    // Allocate memory for group strings
    char **groups = malloc(token_count * sizeof(char *));
    if (groups == NULL) {
        *return_size = 0;
        return NULL;
    }

    // Second pass: extract non-empty tokens
    current = original;
    for (int i = 0; i < token_count; i++) {
        if (i > 0) {
            current = strstr(current, " ") + 1;
            // Skip any leading spaces
            while (*current == ' ') {
                current++;
            }
        }
        size_t len = strlen(current);
        if (len == 0) {
            free(groups);
            *return_size = 0;
            return NULL;
        }
        groups[i] = malloc(len + 1);
        if (groups[i] == NULL) {
            free(groups);
            *return_size = 0;
            return NULL;
        }
        strncpy(groups[i], current, len);
        groups[i][len] = '\0';
    }

    int *result = malloc(token_count * sizeof(int));
    for (int i = 0; i < token_count; i++) {
        result[i] = parse_paren_group_c(groups[i]);
    }

    *return_size = token_count;
    return result;
}

void test1() {
    char *input = "(()()) ((())) () ((())()())";
    int size;
    int *result = parse_nested_parens_c(input, &size);
    assert(result != NULL && size == 4);
    assert(result[0] == 2 && result[1] == 3 && result[2] == 1 && result[3] == 3);
    free(result);
}

void test2() {
    char *input = "() (()) ((())) (((())))";
    int size;
    int *result = parse_nested_parens_c(input, &size);
    assert(result != NULL && size == 4);
    assert(result[0] == 1 && result[1] == 2 && result[2] == 3 && result[3] == 4);
    free(result);
}

int main() {
    test1();
    test2();
    return 0;
}