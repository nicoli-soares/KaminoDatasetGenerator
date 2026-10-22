int triples_sum_to_zero_c(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            for (int k = j + 1; k < len; k++) {
                if (arr[i] + arr[j] + arr[k] == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void test_triples_sum_to_zero_c() {
    int test1[] = {1, 3, 5, 0}; assert(triples_sum_to_zero_c(test1, 4) == 0);
    int test2[] = {1, 3, -2, 1}; assert(triples_sum_to_zero_c(test2, 4) == 1);
    int test3[] = {1, 2, 3, 7}; assert(triples_sum_to_zero_c(test3, 4) == 0);
    int test4[] = {2, 4, -5, 3, 9, 7}; assert(triples_sum_to_zero_c(test4, 6) == 1);
    int test5[] = {1}; assert(triples_sum_to_zero_c(test5, 1) == 0);
    int test6[] = {1, 3, 5, -100}; assert(triples_sum_to_zero_c(test6, 4) == 0);
    int test7[] = {100, 3, 5, -100}; assert(triples_sum_to_zero_c(test7, 4) == 0);
    int test8[] = {1, 3, 5, -1}; assert(triples_sum_to_zero_c(test8, 4) == 0);
}

int main() {
    test_triples_sum_to_zero_c();
    return 0;
}