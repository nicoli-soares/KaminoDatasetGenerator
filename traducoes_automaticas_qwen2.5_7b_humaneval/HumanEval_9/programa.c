#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definindo a struct para armazenar o running max
typedef struct {
    int value;
} RunningMaxStruct;

// Definindo a struct para armazenar o resultado
typedef struct {
    int *result;
    int result_size;
} RollingMaxResultStruct;

// Função para calcular o rolling max
int rolling_max_c(int numbers[], int size, int *result) {
    int running_max = numbers[0];
    for (int i = 0; i < size; i++) {
        if (numbers[i] > running_max) {
            running_max = numbers[i];
        }
        result[i] = running_max;
    }
    return 0;
}

// Função de teste
void test_rolling_max_c() {
    int numbers[] = {1, 2, 3, 2, 3, 4, 2};
    int expected[] = {1, 2, 3, 3, 3, 4, 4};
    int result[7];
    rolling_max_c(numbers, 7, result);
    int i;
    for (i = 0; i < 7; i++) {
        assert(result[i] == expected[i]);
    }
}

int main() {
    test_rolling_max_c();
    printf("All tests passed.\n");
    return 0;
}