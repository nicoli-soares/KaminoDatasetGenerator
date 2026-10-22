typedef struct {
    int value;
} IntValue;

int triples_sum_to_zero_c(int *list, int len, int *result) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            for (int k = j + 1; k < len; k++) {
                if (list[i] + list[j] + list[k] == 0) {
                    *result = 1;
                    return 0;
                }
            }
        }
    }
    *result = 0;
    return 0;
}

void test_triple_sum() {
    int result;
    
    // Test case 1: Should return False
    int test1[] = {1, 3, 5, 0};
    triples_sum_to_zero_c(test1, 4, &result);
    assert(result == 0);
    
    // Test case 2: Should return False
    int test2[] = {1, 3, 5, -1};
    triples_sum_to_zero_c(test2, 4, &result);
    assert(result == 0);
    
    // Test case 3: Should return True
    int test3[] = {1, 3, -2, 1};
    triples_sum_to_zero_c(test3, 4, &result);
    assert(result == 1);
    
    // Test case 4: Should return False
    int test4[] = {1, 2, 3, 7};
    triples_sum_to_zero_c(test4, 4, &result);
    assert(result == 0);
    
    // Test case 5: Should return False
    int test5[] = {1, 2, 5, 7};
    triples_sum_to_zero_c(test5, 4, &result);
    assert(result == 0);
    
    // Test case 6: Should return True
    int test6[] = {2, 4, -5, 3, 9, 7};
    triples_sum_to_zero_c(test6, 6, &result);
    assert(result == 1);
    
    // Test case 7: Should return False
    int test7[] = {1};
    triples_sum_to_zero_c(test7, 1, &result);
    assert(result == 0);
    
    // Test case 8: Should return False
    int test8[] = {1, 3, 5, -100};
    triples_sum_to_zero_c(test8, 4, &result);
    assert(result == 0);
    
    // Test case 9: Should return False
    int test9[] = {100, 3, 5, -100};
    triples_sum_to_zero_c(test9, 4, &result);
    assert(result == 0);
}

int main() {
    test_triple_sum();
    return 0;
}