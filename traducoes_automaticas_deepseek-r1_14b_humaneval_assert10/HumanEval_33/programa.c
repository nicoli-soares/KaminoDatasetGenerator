int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void sort_third_c(int* arr, int size) {
    int sub_size = (size + 2) / 3;
    int* subarray = malloc(sub_size * sizeof(int));

    for (int i = 0; i < sub_size; i++) {
        subarray[i] = arr[i * 3];
    }

    qsort(subarray, sub_size, sizeof(int), cmp);

    for (int i = 0; i < sub_size; i++) {
        arr[i * 3] = subarray[i];
    }

    free(subarray);
}

void test_case_1() {
    int arr[] = {1, 2, 3};
    int size = sizeof(arr)/sizeof(arr[0]);
    sort_third_c(arr, size);
    assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 3);
}

void test_case_2() {
    int arr[] = {5,6,3,4,8,9,2};
    int size = sizeof(arr)/sizeof(arr[0]);
    sort_third_c(arr, size);
    assert(arr[0] == 2 && arr[1] ==6 && arr[2] ==3 && arr[3] ==4 && arr[4] ==8 && arr[5] ==9 && arr[6] ==5);
}

void test_case_3() {
    int arr[] = {5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10};
    int size = sizeof(arr)/sizeof(arr[0]);
    sort_third_c(arr, size);
    assert(arr[0] == 1 && arr[1] ==3 && arr[2] ==-5 && arr[3] ==2 && arr[4] ==-3 && arr[5] ==3 && arr[6] ==5 && arr[7] ==0 && arr[8] ==123 && arr[9] ==9 && arr[10] ==-10);
}

void test_case_4() {
    int arr[] = {5, 8, -12, 4, 23, 2, 3, 11, 12, -10};
    int size = sizeof(arr)/sizeof(arr[0]);
    sort_third_c(arr, size);
    assert(arr[0] == -10 && arr[1] ==8 && arr[2] ==-12 && arr[3] ==3 && arr[4] ==23 && arr[5] ==2 && arr[6] ==4 && arr[7] ==11 && arr[8] ==12 && arr[9] ==5);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}