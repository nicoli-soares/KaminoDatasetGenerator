#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int longest(char** strings, int count, char** out) {
    if (count == 0) {
        return -1; // Indica que a lista está vazia (None)
    }
    int maxlen = 0;
    for (int i = 0; i < count; ++i) {
        int len = 0;
        const char* s = strings[i];
        while (*s++ != '\0') {
            ++len;
        }
        if (len > maxlen) {
            maxlen = len;
        }
    }
    for (int i = 0; i < count; ++i) {
        int len = 0;
        const char* s = strings[i];
        while (*s++ != '\0') {
            ++len;
        }
        if (len == maxlen) {
            *out = strings[i];
            return 0; // Sucesso
        }
    }
    return -1; // Não deveria chegar aqui
}

void test_empty() {
    char* result = NULL;
    int status = longest(NULL, 0, &result);
    assert(status == -1);
    assert(result == NULL);
}

void test_single() {
    char* arr[3] = {"x", "y", "z"};
    char* result = NULL;
    int status = longest(arr, 3, &result);
    assert(status == 0);
    const char* expected = "x";
    const char* r = result;
    const char* e = expected;
    int eq = 1;
    while (*e && *r) {
        if (*e != *r) {
            eq = 0;
            break;
        }
        ++e;
        ++r;
    }
    if (*e || *r) {
        eq = 0;
    }
    assert(eq);
}

void test_multiple() {
    char* arr[6] = {"x", "yyy", "zzzz", "www", "kkkk", "abc"};
    char* result = NULL;
    int status = longest(arr, 6, &result);
    assert(status == 0);
    const char* expected = "zzzz";
    const char* r = result;
    const char* e = expected;
    int eq = 1;
    while (*e && *r) {
        if (*e != *r) {
            eq = 0;
            break;
        }
        ++e;
        ++r;
    }
    if (*e || *r) {
        eq = 0;
    }
    assert(eq);
}

int main(void) {
    test_empty();
    test_single();
    test_multiple();
    return 0;
}