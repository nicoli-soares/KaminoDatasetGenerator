#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Função principal
int car_race_collision(int n) {
    // Calcula o quadrado de n
    return n * n;
}

// Testes
void test_car_race_collision() {
    // Testes baseados nos casos fornecidos
    assert(car_race_collision(2) == 4);
    assert(car_race_collision(3) == 9);
    assert(car_race_collision(4) == 16);
    assert(car_race_collision(8) == 64);
    assert(car_race_collision(10) == 100);
}

// Função main que executa os testes
int main(void) {
    test_car_race_collision();
    return 0;
}