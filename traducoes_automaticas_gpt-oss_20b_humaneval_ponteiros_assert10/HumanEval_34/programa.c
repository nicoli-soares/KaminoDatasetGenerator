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
    int data[256];
    int size;
} UniqueResult;

void unique(const int *input, int n, UniqueResult *out) {
    int unique_vals[256];
    int uniq_count = 0;

    // Collect unique values
    for (int i = 0; i < n; i++) {
        int val = input[i];
        int found = 0;
        for (int j = 0; j < uniq_count; j++) {
            if (unique_vals[j] == val) {
                found = 1;
                break;
            }
        }
        if (!found && uniq_count < 256) {
            unique_vals[uniq_count++] = val;
        }
    }

    // Simple insertion sort on unique_vals
    for (int i = 1; i < uniq_count; i++) {
        int key = unique_vals[i];
        int j = i - 1;
        while (j >= 0 && unique_vals[j] > key) {
            unique_vals[j + 1] = unique_vals[j];
            j--;
        }
        unique_vals[j + 1] = key;
    }

    // Copy sorted unique values to output
    out->size = uniq_count;
    for (int i = 0; i < uniq_count; i++) {
        out->data[i] = unique_vals[i];
    }
}

/* Test for the unique function */
void test_unique(void) {
    int input[] = {5, 3, 5, 2, 3, 3, 9, 0, 123};
    int expected[] = {0, 2, 3, 5, 9, 123};
    UniqueResult result;

    unique(input, sizeof(input)/sizeof(input[0]), &result);

    // Check size
    assert(result.size == 6);

    // Check each element
    for (int i = 0; i < result.size; i++) {
        assert(result.data[i] == expected[i]);
    }
}

/* Main function that runs all tests */
int main(void) {
    test_unique();
    return 0;
}