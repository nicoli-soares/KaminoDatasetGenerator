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
    const char *word;
    int value;
} WordMap;

static const WordMap value_map[10] = {
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

int get_value(const char *word) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(word, value_map[i].word) == 0) {
            return value_map[i].value;
        }
    }
    return 10; // desconhecido, mas não ocorre nos testes
}

int compare_word(const void *a, const void *b) {
    const char *wa = *(const char **)a;
    const char *wb = *(const char **)b;
    int va = get_value(wa);
    int vb = get_value(wb);
    return va - vb;
}

char *sort_numbers(const char *numbers) {
    if (numbers == NULL) {
        return NULL;
    }
    size_t len = strlen(numbers);
    char *input_copy = (char *)malloc(len + 1);
    if (!input_copy) {
        return NULL;
    }
    strcpy(input_copy, numbers);

    char *tokens[100];
    int count = 0;
    char *tok = strtok(input_copy, " ");
    while (tok != NULL) {
        if (strlen(tok) > 0) {
            tokens[count++] = tok;
            if (count >= 100) {
                break; // limite de segurança
            }
        }
        tok = strtok(NULL, " ");
    }

    qsort(tokens, count, sizeof(char *), compare_word);

    size_t out_len = 1; // pelo menos o terminador nulo
    if (count > 0) {
        out_len = 0;
        for (int i = 0; i < count; i++) {
            out_len += strlen(tokens[i]) + 1; // espaço ou terminador
        }
        out_len -= 1; // remove espaço extra após o último
        out_len += 1; // adiciona terminador nulo
    }

    char *output = (char *)malloc(out_len);
    if (!output) {
        free(input_copy);
        return NULL;
    }

    char *p = output;
    for (int i = 0; i < count; i++) {
        size_t l = strlen(tokens[i]);
        memcpy(p, tokens[i], l);
        p += l;
        if (i != count - 1) {
            *p = ' ';
            p++;
        }
    }
    *p = '\0';

    free(input_copy);
    return output;
}

/* Test functions */

void test_empty() {
    char *res = sort_numbers("");
    assert(res != NULL);
    assert(strcmp(res, "") == 0);
    free(res);
}

void test_single() {
    char *res = sort_numbers("three");
    assert(res != NULL);
    assert(strcmp(res, "three") == 0);
    free(res);
}

void test_three_five_nine() {
    char *res = sort_numbers("three five nine");
    assert(res != NULL);
    assert(strcmp(res, "three five nine") == 0);
    free(res);
}

void test_five_zero_four_seven_nine_eight() {
    char *res = sort_numbers("five zero four seven nine eight");
    assert(res != NULL);
    assert(strcmp(res, "zero four five seven eight nine") == 0);
    free(res);
}

void test_six_five_four_three_two_one_zero() {
    char *res = sort_numbers("six five four three two one zero");
    assert(res != NULL);
    assert(strcmp(res, "zero one two three four five six") == 0);
    free(res);
}

int main() {
    test_empty();
    test_single();
    test_three_five_nine();
    test_five_zero_four_seven_nine_eight();
    test_six_five_four_three_two_one_zero();
    return 0;
}