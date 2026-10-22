int max_element_c(int *arr, int n, size_t size) {
    int m = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > m) {
            m = arr[i];
        }
    }
    return m;
}

void check() {
    int test1[] = {1, 2, 3};
    assert(max_element_c(test1, 3, sizeof(int)) == 3);
    
    int test2[] = {5, 3, -5, 2, -3, 3, 9, 0, 124, 1, -10};
    assert(max_element_c(test2, 11, sizeof(int)) == 124);
}

int main() {
    check();
    return 0;
}