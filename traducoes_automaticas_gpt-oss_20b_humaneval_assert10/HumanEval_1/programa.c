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
    char **items;
    int count;
} StringArray;

typedef struct {
    char *data;
    int len;
    int cap;
} CurrentStringBuffer;

void init_buffer(CurrentStringBuffer *b) {
    b->cap = 16;
    b->len = 0;
    b->data = malloc(b->cap);
}

void append_char(CurrentStringBuffer *b, char c) {
    if (b->len + 1 >= b->cap) {
        b->cap *= 2;
        b->data = realloc(b->data, b->cap);
    }
    b->data[b->len++] = c;
}

void clear_buffer(CurrentStringBuffer *b) {
    b->len = 0;
}

void free_string_array(StringArray *arr) {
    for (int i = 0; i < arr->count; ++i) {
        free(arr->items[i]);
    }
    free(arr->items);
    arr->items = NULL;
    arr->count = 0;
}

StringArray separate_paren_groups(const char *paren_string) {
    StringArray result = {NULL, 0};
    int res_cap = 10;
    result.items = malloc(res_cap * sizeof(char*));

    CurrentStringBuffer cur;
    init_buffer(&cur);
    int current_depth = 0;

    for (const char *p = paren_string; *p != '\0'; ++p) {
        char c = *p;
        if (c == ' ') continue;

        if (c == '(') {
            current_depth++;
            append_char(&cur, c);
        } else if (c == ')') {
            current_depth--;
            append_char(&cur, c);
            if (current_depth == 0) {
                char *group = malloc(cur.len + 1);
                memcpy(group, cur.data, cur.len);
                group[cur.len] = '\0';
                if (result.count >= res_cap) {
                    res_cap *= 2;
                    result.items = realloc(result.items, res_cap * sizeof(char*));
                }
                result.items[result.count++] = group;
                clear_buffer(&cur);
            }
        }
    }

    free(cur.data);
    return result;
}

/* Test functions */

void test1() {
    StringArray res = separate_paren_groups("(()()) ((())) () ((())()())");
    assert(res.count == 4);
    const char *expected[4] = {"(()())", "((()))", "()", "((())()())"};
    for (int i = 0; i < 4; ++i) {
        assert(strcmp(res.items[i], expected[i]) == 0);
    }
    free_string_array(&res);
}

void test2() {
    StringArray res = separate_paren_groups("() (()) ((())) (((())))");
    assert(res.count == 4);
    const char *expected[4] = {"()", "(())", "((()))", "(((())))"};
    for (int i = 0; i < 4; ++i) {
        assert(strcmp(res.items[i], expected[i]) == 0);
    }
    free_string_array(&res);
}

void test3() {
    StringArray res = separate_paren_groups("(()(())((())))");
    assert(res.count == 1);
    assert(strcmp(res.items[0], "(()(())((())))") == 0);
    free_string_array(&res);
}

void test4() {
    StringArray res = separate_paren_groups("( ) (( )) (( )( ))");
    assert(res.count == 3);
    const char *expected[3] = {"()", "(())", "(()())"};
    for (int i = 0; i < 3; ++i) {
        assert(strcmp(res.items[i], expected[i]) == 0);
    }
    free_string_array(&res);
}

/* Main */
int main(void) {
    test1();
    test2();
    test3();
    test4();
    return 0;
}