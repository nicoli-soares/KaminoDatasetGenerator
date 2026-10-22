#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int fizz_buzz_c(int n) {
    int count = 0;
    int size = n * 4; // Cálculo do tamanho baseado no maior tamanho possível de n
    char *result_str = malloc(size * sizeof(char)); 
    int num_count = 0;

    for (int i = 0; i < n; i++) {
        if (i % 11 == 0 || i % 13 == 0) {
            if (num_count > 0) {
                sprintf(result_str + num_count, ",%d", i);
                num_count += strlen(result_str + num_count);
            } else {
                sprintf(result_str, "%d", i);
                num_count = strlen(result_str);
            }
        }
    }

    int seven_count = 0;
    for (int i = 0; i < num_count; i++) {
        if (result_str[i] == '7') {
            seven_count++;
        }
    }

    free(result_str);
    return seven_count;
}

void test_fizz_buzz() {
    assert(fizz_buzz_c(50) == 0);
    assert(fizz_buzz_c(78) == 2);
    assert(fizz_buzz_c(79) == 3);
    assert(fizz_buzz_c(100) == 3);
    assert(fizz_buzz_c(200) == 6);
    assert(fizz_buzz_c(4000) == 192);
    assert(fizz_buzz_c(10000) == 639);
    assert(fizz_buzz_c(100000) == 8026);
}

int main() {
    test_fizz_buzz();
    return 0;
}