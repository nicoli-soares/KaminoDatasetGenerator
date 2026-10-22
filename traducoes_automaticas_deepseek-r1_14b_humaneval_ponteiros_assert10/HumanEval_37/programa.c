/* Implementação da função sort_even em C */
#include <assert.h>

void simple_sort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (array[i] > array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void sort_even_c(const int input[], int len_input, int output[]) {
    int even_count = (len_input + 1) / 2;
    int odd_count = len_input / 2;
    
    int evens[even_count];
    int odds[odd_count];
    
    for (int i = 0; i < len_input; i++) {
        if (i % 2 == 0) {
            evens[i / 2] = input[i];
        } else {
            odds[i / 2] = input[i];
        }
    }
    
    simple_sort(evens, even_count);
    
    int output_index = 0;
    for (int i = 0; i < odd_count; i++) {
        output[output_index++] = evens[i];
        output[output_index++] = odds[i];
    }
    
    if (even_count > odd_count) {
        output[output_index] = evens[odd_count];
    }
}

void test_case_1() {
    const int input[] = {1, 2, 3};
    int len_input = 3;
    int output[3];
    
    sort_even_c(input, len_input, output);
    
    assert(output[0] == 1 && output[1] == 2 && output[2] == 3);
}

void test_case_2() {
    const int input[] = {5, 6, 3, 4};
    int len_input = 4;
    int output[4];
    
    sort_even_c(input, len_input, output);
    
    assert(output[0] == 3 && output[1] == 6 && output[2] == 5 && output[3] == 4);
}

int main() {
    test_case_1();
    test_case_2();
    
    return 0;
}