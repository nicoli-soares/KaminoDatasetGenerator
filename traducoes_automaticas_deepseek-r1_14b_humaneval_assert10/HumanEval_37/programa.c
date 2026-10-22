#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int* sort_even_c(int *arr, int n) {
    int evens_len = (n + 1) / 2;
    int odds_len = n / 2;

    int *evens = malloc(evens_len * sizeof(int));
    int *odds = malloc(odds_len * sizeof(int));

    int even_idx = 0, odd_idx = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            evens[even_idx++] = arr[i];
        } else {
            odds[odd_idx++] = arr[i];
        }
    }

    qsort(evens, evens_len, sizeof(int), compare_ints);

    int result_len = (evens_len > odds_len) ? (2 * evens_len - 1) : 2 * odds_len;
    int *result = malloc(result_len * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < evens_len && j < odds_len) {
        result[k++] = evens[i++];
        result[k++] = odds[j++];
    }

    if (i < evens_len) {
        result[k++] = evens[i];
    }

    free(evens);
    free(odds);
    return result;
}

int arrays_equal(int *a, int *b, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    // Test Case 1
    int test_case_1[] = {1, 2, 3};
    int n = sizeof(test_case_1) / sizeof(int);
    int *result = sort_even_c(test_case_1, n);
    int expected_1[] = {1, 2, 3};
    int expected_len = sizeof(expected_1) / sizeof(int);
    int result_len = (n + 1)/2 > (n/2) ? (2*((n+1)/2)-1) : 2*(n/2);
    assert(arrays_equal(result, expected_1, result_len));
    free(result);

    // Test Case 2
    int test_case_2[] = {5, 6, 3, 4};
    n = sizeof(test_case_2) / sizeof(int);
    result = sort_even_c(test_case_2, n);
    int expected_2[] = {3, 6, 5, 4};
    expected_len = sizeof(expected_2) / sizeof(int);
    result_len = (n + 1)/2 > (n/2) ? (2*((n+1)/2)-1) : 2*(n/2);
    assert(arrays_equal(result, expected_2, result_len));
    free(result);

    // Test Case 3
    int test_case_3[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    n = sizeof(test_case_3) / sizeof(int);
    result = sort_even_c(test_case_3, n);
    int expected_3[] = {-10, 3, -5, 2, -3, 3, 5, 0, 9, 1, 123};
    expected_len = sizeof(expected_3) / sizeof(int);
    result_len = (n + 1)/2 > (n/2) ? (2*((n+1)/2)-1) : 2*(n/2);
    assert(arrays_equal(result, expected_3, result_len));
    free(result);

    printf("All test cases passed\n");
    return 0;
}