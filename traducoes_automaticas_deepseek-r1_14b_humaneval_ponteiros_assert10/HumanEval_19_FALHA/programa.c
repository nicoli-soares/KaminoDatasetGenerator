typedef struct {
    char *word;
    int value;
} WordValue;

WordValue value_map[] = {
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

char **split(const char *s, int *len) {
    char **tokens = NULL;
    *len = 0;
    const char *start = s;
    const char *end = s;
    while (*start != '\0') {
        if (*start == ' ') {
            if (end > start) {
                tokens = realloc(tokens, (*len + 1) * sizeof(char *));
                if (tokens == NULL) {
                    free(tokens);
                    return NULL;
                }
                tokens[*len] = strndup(start, end - start);
                if (tokens[*len] == NULL) {
                    free(tokens);
                    return NULL;
                }
                (*len)++;
            }
            start++;
            end = start;
        } else {
            end++;
        }
    }
    if (end > start) {
        tokens = realloc(tokens, (*len + 1) * sizeof(char *));
        if (tokens == NULL) {
            free(tokens);
            return NULL;
        }
        tokens[*len] = strndup(start, end - start);
        if (tokens[*len] == NULL) {
            free(tokens);
            return NULL;
        }
        (*len)++;
    }
    return tokens;
}

int compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    int val1 = -1, val2 = -1;
    int i = 0;
    while (i < sizeof(value_map)/sizeof(value_map[0])) {
        if (strcmp(str1, value_map[i].word) == 0) {
            val1 = value_map[i].value;
            break;
        }
        i++;
    }
    i = 0;
    while (i < sizeof(value_map)/sizeof(value_map[0])) {
        if (strcmp(str2, value_map[i].word) == 0) {
            val2 = value_map[i].value;
            break;
        }
        i++;
    }
    return val1 - val2;
}

char *sort_numbers(char *input) {
    if (input == NULL || *input == '\0') {
        return strdup("");
    }
    int len;
    char **tokens = split(input, &len);
    if (tokens == NULL) {
        return strdup("");
    }
    qsort(tokens, len, sizeof(char *), compare);
    char *result = malloc(strlen(input) + 1);
    if (result == NULL) {
        free(tokens);
        return NULL;
    }
    if (len == 0) {
        result[0] = '\0';
    } else {
        strcpy(result, tokens[0]);
        for (int i = 1; i < len; i++) {
            strcat(result, " ");
            if (strcat(result, tokens[i]) == NULL) {
                free(result);
                free(tokens);
                return NULL;
            }
        }
    }
    free(tokens);
    return result;
}

void check() {
    assert(strcmp(sort_numbers(""), "") == 0);
    assert(strcmp(sort_numbers("three"), "three") == 0);
    assert(strcmp(sort_numbers("three five nine"), "three five nine") == 0);
    assert(strcmp(sort_numbers("five zero four seven nine eight"), "zero four five seven eight nine") == 0);
    assert(strcmp(sort_numbers("six five four three two one zero"), "zero one two three four five six") == 0);
}

int main() {
    check();
    return 0;
}