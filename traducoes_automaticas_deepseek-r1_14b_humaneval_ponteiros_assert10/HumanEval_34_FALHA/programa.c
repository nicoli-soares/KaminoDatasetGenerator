#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    bool seen;
    int value;
} Element;

static int compare_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void unique_c(int input[], int size, int output[]) {
    Element elements[size];
    int unique_count = 0;

    for (int i = 0; i < size; i++) {
        bool is_unique = true;
        for (int j = 0; j < unique_count; j++) {
            if (elements[j].value == input[i]) {
                is_unique = false;
                elements[j].seen = true;
                break;
            }
        }
        if (is_unique) {
            elements[unique_count].value = input[i];
            elements[unique_count].seen = true;
            unique_count++;
        }
    }

    qsort(output, unique_count, sizeof(int), compare_int);
}

int test_unique_c() {
    int input[] = {5, 3, 5, 2, 3, 3, 9, 0, 123};
    int expected[] = {0, 2, 3, 5, 9, 123};
    int output[sizeof(expected)/sizeof(expected[0])];
    
    unique_c(input, sizeof(input)/sizeof(input[0]), output);
    
    for (int i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
        if (output[i] != expected[i]) {
            return -1;
        }
    }
    return 0;
}

int main() {
    assert(test_unique_c() == 0);
    return 0;
}