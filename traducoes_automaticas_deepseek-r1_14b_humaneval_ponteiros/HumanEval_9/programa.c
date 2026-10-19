typedef struct {
    int value;
} RollingMaxValue;

int* rolling_max_c(int numbers[], int len, int* result_len) {
    if (len == 0) {
        *result_len = 0;
        return NULL;
    }

    int* result = (int*)malloc(len * sizeof(int));
    if (result == NULL) {
        *result_len = 0;
        return NULL;
    }

    int running_max = numbers[0];
    result[0] = running_max;

    for (int i = 1; i < len; i++) {
        if (numbers[i] > running_max) {
            running_max = numbers[i];
        }
        result[i] = running_max;
    }

    *result_len = len;
    return result;
}

void test_rolling_max_c_empty() {
    int input[] = {};
    int output_len = 0;
    int* output = rolling_max_c(input, 0, &output_len);
    assert(output_len == 0);
    if (output != NULL) free(output);
}

void test_rolling_max_c_increasing() {
    int input[] = {1, 2, 3, 4};
    int output_len = 0;
    int* output = rolling_max_c(input, 4, &output_len);
    assert(output_len == 4);
    assert(output[0] == 1);
    assert(output[1] == 2);
    assert(output[2] == 3);
    assert(output[3] == 4);
    free(output);
}

void test_rolling_max_c_decreasing() {
    int input[] = {4, 3, 2, 1};
    int output_len = 0;
    int* output = rolling_max_c(input, 4, &output_len);
    assert(output_len == 4);
    assert(output[0] == 4);
    assert(output[1] == 4);
    assert(output[2] == 4);
    assert(output[3] == 4);
    free(output);
}

void test_rolling_max_c_peak() {
    int input[] = {3, 2, 3, 100, 3};
    int output_len = 0;
    int* output = rolling_max_c(input, 5, &output_len);
    assert(output_len == 5);
    assert(output[0] == 3);
    assert(output[1] == 3);
    assert(output[2] == 3);
    assert(output[3] == 100);
    assert(output[4] == 100);
    free(output);
}

int main() {
    test_rolling_max_c_empty();
    test_rolling_max_c_increasing();
    test_rolling_max_c_decreasing();
    test_rolling_max_c_peak();
    return 0;
}