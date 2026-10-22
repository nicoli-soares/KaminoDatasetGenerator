#include <assert.h>
#include <stdlib.h>

int* get_positive_c(int* l, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (l[i] > 0) {
            count++;
        }
    }
    int* result = (int*)malloc(count * sizeof(int));
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (l[i] > 0) {
            result[index++] = l[i];
        }
    }
    return result;
}

int compare_arrays(int* a, int* b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void test_positive() {
    int test1_input[] = {-1, -2, 4, 5, 6};
    int test1_expected[] = {4, 5, 6};
    int test1_size = sizeof(test1_input) / sizeof(test1_input[0]);
    int test1_expected_size = sizeof(test1_expected) / sizeof(test1_expected[0]);
    
    int* result = get_positive_c(test1_input, test1_size);
    assert(compare_arrays(result, test1_expected, test1_expected_size) == 1);
    free(result);

    int test2_input[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int test2_expected[] = {5, 3, 2, 3, 9, 123, 1};
    int test2_size = sizeof(test2_input) / sizeof(test2_input[0]);
    int test2_expected_size = sizeof(test2_expected) / sizeof(test2_expected[0]);
    
    int* result2 = get_positive_c(test2_input, test2_size);
    assert(compare_arrays(result2, test2_expected, test2_expected_size) == 1);
    free(result2);

    int test3_input[] = {-1, -2};
    int test3_expected[] = {};
    int test3_size = sizeof(test3_input) / sizeof(test3_input[0]);
    int test3_expected_size = sizeof(test3_expected) / sizeof(test3_expected[0]);
    
    int* result3 = get_positive_c(test3_input, test3_size);
    assert(compare_arrays(result3, test3_expected, test3_expected_size) == 1);
    free(result3);

    int test4_input[] = {};
    int test4_expected[] = {};
    int test4_size = sizeof(test4_input) / sizeof(test4_input[0]);
    int test4_expected_size = sizeof(test4_expected) / sizeof(test4_expected[0]);
    
    int* result4 = get_positive_c(test4_input, test4_size);
    assert(compare_arrays(result4, test4_expected, test4_expected_size) == 1);
    free(result4);
}

int main() {
    test_positive();
    return 0;
}