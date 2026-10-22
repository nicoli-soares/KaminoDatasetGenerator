typedef struct {
    int value;
} Element;

int _is_unique(int arr[], int len, int value) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == value) {
            return 0;
        }
    }
    return 1;
}

void sort_c(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int unique_c(int arr[], int len, int result[]) {
    int unique_count = 0;
    for (int i = 0; i < len; i++) {
        if (_is_unique(arr, i, arr[i])) {
            result[unique_count++] = arr[i];
        }
    }
    sort_c(result, unique_count);
    return unique_count;
}

void test_unique() {
    int input[] = {5, 3, 5, 2, 3, 3, 9, 0, 123};
    int len = sizeof(input)/sizeof(input[0]);
    int result[9];
    int size = unique_c(input, len, result);
    
    int expected[] = {0, 2, 3, 5, 9, 123};
    for (int i = 0; i < 6; i++) {
        assert(result[i] == expected[i]);
    }
}

int main() {
    test_unique();
    return 0;
}