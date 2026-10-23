#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int strlen_c(const char *string) {
    int len = 0;
    while (string[len] != '\0') {
        len++;
    }
    return len;
}

void check(int (*candidate)(const char *)) {
    assert(candidate("") == 0);
    assert(candidate("x") == 1);
    assert(candidate("asdasnakj") == 9);
}

int main(void) {
    check(strlen_c);
    return 0;
}