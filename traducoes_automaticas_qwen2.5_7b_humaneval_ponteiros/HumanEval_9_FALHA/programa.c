#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    int value;
} RollingMaxElement;

typedef struct {
    int *numbers;
    int length;
} NumberList;

int max(int a, int b) {
    return a > b ? a : b;
}

void rolling_max_c(NumberList *numbers, int *result, int *result_length) {
    if (numbers->length == 0) {
        *result_length = 0;
        return;
    }

    *result_length = numbers->length;
    RollingMaxElement *result_array = (RollingMaxElement *)malloc(*result_length * sizeof(RollingMaxElement));
    if (result_array == NULL) {
        *result_length = 0;
        return;
    }

    int running_max = numbers->numbers[0];
    result_array[0].value = running_max;

    for (int i = 1; i < numbers->length; i++) {
        running_max = max(running_max, numbers->numbers[i]);
        result_array[i].value = running_max;
    }

    for (int i = 0; i < *result_length; i++) {
        result[i] = result_array[i].value;
    }

    free(result_array);
}

int main() {
    // Test case 1
    int numbers1[] = {};
    int result1[100];
    int result_length1;
    rolling_max_c((NumberList *)&numbers1, result1, &result_length1);
    assert(result_length1 == 0);

    // Test case 2
    int numbers2[] = {1, 2, 3, 4};
    int result2[4];
    int result_length2;
    rolling_max_c((NumberList *)&numbers2, result2, &result_length2);
    assert(result_length2 == 4 && result2[0] == 1 && result2[1] == 2 && result2[2] == 3 && result2[3] == 4);

    // Test case 3
    int numbers3[] = {4, 3, 2, 1};
    int result3[4];
    int result_length3;
    rolling_max_c((NumberList *)&numbers3, result3, &result_length3);
    assert(result_length3 == 4 && result3[0] == 4 && result3[1] == 4 && result3[2] == 4 && result3[3] == 4);

    // Test case 4
    int numbers4[] = {3, 2, 3, 100, 3};
    int result4[5];
    int result_length4;
    rolling_max_c((NumberList *)&numbers4, result4, &result_length4);
    assert(result_length4 == 5 && result4[0] == 3 && result4[1] == 3 && result4[2] == 3 && result4[3] == 100 && result4[4] == 100);

    printf("All tests passed!\n");
    return 0;
}