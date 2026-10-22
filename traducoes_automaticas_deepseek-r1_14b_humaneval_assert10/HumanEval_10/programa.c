typedef struct {
    char* key;
    char* value;
} StringValuePair;

int strlen_c(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char* substr_c(char* str, int start, int length) {
    char* sub = malloc(length + 1);
    strncpy(sub, str + start, length);
    sub[length] = '\0';
    return sub;
}

char* strcon_c(char* a, char* b) {
    char* result = malloc(strlen_c(a) + strlen_c(b) + 1);
    strcpy(result, a);
    strcat(result, b);
    return result;
}

int is_palindrome_c(char* str) {
    int len = strlen_c(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

char* reverse_c(char* str) {
    int len = strlen_c(str);
    char* reversed = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

char* make_palindrome_c(char* string) {
    if (string == NULL || *string == '\0') {
        return strdup(string);
    }

    int beginning_of_suffix = 0;
    char* original = strdup(string);
    char* result = NULL;

    while (!is_palindrome_c(original + beginning_of_suffix)) {
        beginning_of_suffix++;
    }

    int prefix_length = beginning_of_suffix;
    char* prefix = substr_c(original, 0, prefix_length);
    char* reversed_prefix = reverse_c(prefix);
    result = strcon_c(original, reversed_prefix);
    free(prefix);
    free(reversed_prefix);
    free(original);

    return result;
}

void test_make_palindrome_c() {
    assert(strcmp(make_palindrome_c(""), "") == 0);
    assert(strlen_c(make_palindrome_c("x")) == 1);
    assert(strcmp(make_palindrome_c("xyz"), "xyzyx") == 0);
    assert(strcmp(make_palindrome_c("xyx"), "xyx") == 0);
    assert(strcmp(make_palindrome_c("jerry"), "jerryrrej") == 0);
}

int main() {
    test_make_palindrome_c();
    return 0;
}