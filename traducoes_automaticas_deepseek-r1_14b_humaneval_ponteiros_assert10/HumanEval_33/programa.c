int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int* sort_third(int* l, int size) {
    int* copy = malloc(size * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, l, size * sizeof(int));

    int extracted_count = 0;
    int* extracted = malloc((size / 3 + 1) * sizeof(int));
    for (int i = 0; i < size; i += 3) {
        if (i < size) {
            extracted[extracted_count++] = copy[i];
        }
    }

    qsort(extracted, extracted_count, sizeof(int), cmp_int);

    int extracted_idx = 0;
    for (int i = 0; i < size; i += 3) {
        if (extracted_idx < extracted_count) {
            copy[i] = extracted[extracted_idx++];
        }
    }

    free(extracted);
    return copy;
}

int main() {
    // Test case 1
    int test1[] = {1, 2, 3};
    int expected1[] = {1, 2, 3};
    int size1 = sizeof(test1) / sizeof(int);
    int* result1 = sort_third(test1, size1);
    assert(memcmp(result1, expected1, size1 * sizeof(int)) == 0);
    free(result1);

    // Test case 2
    int test2[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int expected2[] = {1, 3, -5, 2, -3, 3, 5, 0, 123, 9, -10};
    int size2 = sizeof(test2) / sizeof(int);
    int* result2 = sort_third(test2, size2);
    assert(memcmp(result2, expected2, size2 * sizeof(int)) == 0);
    free(result2);

    // Test case 3
    int test3[] = {5, 8, -12, 4, 23, 2, 3, 11, 12, -10};
    int expected3[] = {-10, 8, -12, 3, 23, 2, 4, 11, 12, 5};
    int size3 = sizeof(test3) / sizeof(int);
    int* result3 = sort_third(test3, size3);
    assert(memcmp(result3, expected3, size3 * sizeof(int)) == 0);
    free(result3);

    // Test case 4
    int test4[] = {5, 6, 3, 4, 8, 9, 2};
    int expected4[] = {2, 6, 3, 4, 8, 9, 5};
    int size4 = sizeof(test4) / sizeof(int);
    int* result4 = sort_third(test4, size4);
    assert(memcmp(result4, expected4, size4 * sizeof(int)) == 0);
    free(result4);

    // Test case 5
    int test5[] = {5, 8, 3, 4, 6, 9, 2};
    int expected5[] = {2, 8, 3, 4, 6, 9, 5};
    int size5 = sizeof(test5) / sizeof(int);
    int* result5 = sort_third(test5, size5);
    assert(memcmp(result5, expected5, size5 * sizeof(int)) == 0);
    free(result5);

    // Test case 6
    int test6[] = {5, 6, 9, 4, 8, 3, 2};
    int expected6[] = {2, 6, 9, 4, 8, 3, 5};
    int size6 = sizeof(test6) / sizeof(int);
    int* result6 = sort_third(test6, size6);
    assert(memcmp(result6, expected6, size6 * sizeof(int)) == 0);
    free(result6);

    // Test case 7
    int test7[] = {5, 6, 3, 4, 8, 9, 2, 1};
    int expected7[] = {2, 6, 3, 4, 8, 9, 5, 1};
    int size7 = sizeof(test7) / sizeof(int);
    int* result7 = sort_third(test7, size7);
    assert(memcmp(result7, expected7, size7 * sizeof(int)) == 0);
    free(result7);

    return 0;
}