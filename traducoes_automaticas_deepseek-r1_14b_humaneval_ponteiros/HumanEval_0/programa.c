typedef struct {
    float elem;
} Numero;

int has_close_elements_c(const Numero *numbers, int n, float threshold) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                float distance = fabs(numbers[i].elem - numbers[j].elem);
                if (distance < threshold) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void test_has_close_elements_c() {
    Numero test1[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    assert(has_close_elements_c(test1, 6, 0.3) == 1);
    Numero test2[] = {1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    assert(has_close_elements_c(test2, 6, 0.05) == 0);
    Numero test3[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    assert(has_close_elements_c(test3, 5, 0.95) == 1);
    Numero test4[] = {1.0, 2.0, 5.9, 4.0, 5.0};
    assert(has_close_elements_c(test4, 5, 0.8) == 0);
    Numero test5[] = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    assert(has_close_elements_c(test5, 6, 0.1) == 1);
    Numero test6[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    assert(has_close_elements_c(test6, 5, 1.0) == 1);
    Numero test7[] = {1.1, 2.2, 3.1, 4.1, 5.1};
    assert(has_close_elements_c(test7, 5, 0.5) == 0);
}

int main() {
    test_has_close_elements_c();
    return 0;
}