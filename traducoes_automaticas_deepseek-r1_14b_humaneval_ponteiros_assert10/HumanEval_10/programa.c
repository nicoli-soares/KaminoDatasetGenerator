typedef struct {
    char *str;
} PalindromeData;

int is_palindrome(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

void reverse_string(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }
}

char *make_palindrome(const char *string) {
    if (string == NULL || *string == '\0') {
        return strdup("");
    }

    // Check if the entire string is already a palindrome
    if (is_palindrome(string)) {
        return strdup(string);
    }

    int len = strlen(string);
    char *result = strdup(string);

    int i;
    // Start from the end of the string and move backwards
    for (i = len - 1; i >= 0; i--) {
        if (is_palindrome(string + i)) {
            break;
        }
    }

    int prefix_len = i;
    char *prefix = strndup(string, prefix_len);
    reverse_string(prefix);

    int new_len = len + prefix_len + 1;
    char *new_str = malloc(new_len);
    if (new_str == NULL) {
        free(result);
        free(prefix);
        return NULL;
    }

    snprintf(new_str, new_len, "%s%s", result, prefix);
    free(result);
    free(prefix);
    return new_str;
}

void test_make_palindrome() {
    assert(strcmp(make_palindrome(""), "") == 0);
    assert(strcmp(make_palindrome("x"), "x") == 0);
    assert(strcmp(make_palindrome("xyz"), "xyzyx") == 0);
    assert(strcmp(make_palindrome("xyx"), "xyx") == 0);
    assert(strcmp(make_palindrome("jerry"), "jerryrrej") == 0);
}

int main() {
    test_make_palindrome();
    return 0;
}