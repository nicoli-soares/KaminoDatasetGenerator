int below_zero_c(int operations[], int size) {
    int balance = 0;
    
    for (int i = 0; i < size; i++) {
        balance += operations[i];
        if (balance < 0) {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    int arr1[] = {};
    assert(below_zero_c(arr1, 0) == 0);
    
    int arr2[] = {1, 2, -3, 1, 2, -3};
    assert(below_zero_c(arr2, 6) == 0);
    
    int arr3[] = {1, 2, -4, 5, 6};
    assert(below_zero_c(arr3, 5) == 1);
    
    int arr4[] = {1, -1, 2, -2, 5, -5, 4, -4};
    assert(below_zero_c(arr4, 8) == 0);
    
    int arr5[] = {1, -1, 2, -2, 5, -5, 4, -5};
    assert(below_zero_c(arr5, 8) == 1);
    
    int arr6[] = {1, -2, 2, -2, 5, -5, 4, -4};
    assert(below_zero_c(arr6, 8) == 1);
    
    return 0;
}