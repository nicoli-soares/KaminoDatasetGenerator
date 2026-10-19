#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int max_depth;
} ParenGroup;

typedef struct {
    char str[256];
} ParenString;

int parse_paren_group(const char *s, int *max_depth) {
    int depth = 0;
    *max_depth = 0;
    while (*s) {
        if (*s == '(') {
            depth += 1;
            *max_depth = depth > *max_depth ? depth : *max_depth;
        } else if (*s == ')') {
            depth -= 1;
        }
        s++;
    }
    return *max_depth;
}

int parse_nested_parens(const char *paren_string) {
    int n = 0;
    char *token = strtok((char *)paren_string, " ");
    ParenGroup groups[100];
    while (token) {
        int max_depth = 0;
        groups[n].max_depth = parse_paren_group(token, &max_depth);
        n++;
        token = strtok(NULL, " ");
    }
    return n;
}

int main() {
    assert(parse_nested_parens("(()()) ((())) () ((())()())") == 4);
    assert(parse_nested_parens("() (()) ((())) (((())))") == 4);
    assert(parse_nested_parens("(()(())((())))") == 1);
    return 0;
}