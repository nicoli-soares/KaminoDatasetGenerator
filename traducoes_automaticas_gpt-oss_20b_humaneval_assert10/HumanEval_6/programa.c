#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    int depth;
} GroupDepth;

int parse_paren_group(const char* s) {
    int depth = 0;
    int max_depth = 0;
    for (const char* p = s; *p; ++p) {
        if (*p == '(') {
            depth++;
            if (depth > max_depth) {
                max_depth = depth;
            }
        } else if (*p == ')') {
            depth--;
        }
    }
    return max_depth;
}

int* parse_nested_parens(const char* paren_string, size_t* out_len) {
    /* Count the number of non-empty groups separated by spaces */
    size_t count = 0;
    const char* p = paren_string;
    bool prev_space = true;
    while (*p) {
        if (*p != ' ' && prev_space) {
            count++;
            prev_space = false;
        } else if (*p == ' ') {
            prev_space = true;
        } else {
            prev_space = false;
        }
        p++;
    }
    if (count == 0) {
        *out_len = 0;
        return NULL;
    }
    int* result = (int*)malloc(count * sizeof(int));
    if (!result) {
        *out_len = 0;
        return NULL;
    }
    /* Second pass: extract each group and compute its max depth */
    p = paren_string;
    size_t idx = 0;
    const char* token_start = NULL;
    bool in_token = false;
    while (*p) {
        if (*p != ' ') {
            if (!in_token) {
                token_start = p;
                in_token = true;
            }
        } else {
            if (in_token) {
                size_t len = p - token_start;
                char* token = (char*)malloc(len + 1);
                if (!token) {
                    free(result);
                    *out_len = 0;
                    return NULL;
                }
                memcpy(token, token_start, len);
                token[len] = '\0';
                result[idx++] = parse_paren_group(token);
                free(token);
                in_token = false;
            }
        }
        p++;
    }
    if (in_token) {
        size_t len = p - token_start;
        char* token = (char*)malloc(len + 1);
        if (!token) {
            free(result);
            *out_len = 0;
            return NULL;
        }
        memcpy(token, token_start, len);
        token[len] = '\0';
        result[idx++] = parse_paren_group(token);
        free(token);
    }
    *out_len = count;
    return result;
}

bool arrays_equal(const int* a, const int* b, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void test1(void) {
    size_t len;
    int* res = parse_nested_parens("(()()) ((())) () ((())()())", &len);
    int expected[] = {2, 3, 1, 3};
    assert(len == 4);
    assert(arrays_equal(res, expected, len));
    free(res);
}

void test2(void) {
    size_t len;
    int* res = parse_nested_parens("() (()) ((())) (((())))", &len);
    int expected[] = {1, 2, 3, 4};
    assert(len == 4);
    assert(arrays_equal(res, expected, len));
    free(res);
}

void test3(void) {
    size_t len;
    int* res = parse_nested_parens("(()(())((())))", &len);
    int expected[] = {4};
    assert(len == 1);
    assert(arrays_equal(res, expected, len));
    free(res);
}

int main(void) {
    test1();
    test2();
    test3();
    return 0;
}