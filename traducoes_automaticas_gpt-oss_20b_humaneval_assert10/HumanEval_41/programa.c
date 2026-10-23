#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef long long ll;

ll car_race_collision(ll n) {
    return n * n;
}

void test_car_race_collision(void) {
    assert(car_race_collision(2) == 4);
    assert(car_race_collision(3) == 9);
    assert(car_race_collision(4) == 16);
    assert(car_race_collision(8) == 64);
    assert(car_race_collision(10) == 100);
}

int main(void) {
    test_car_race_collision();
    return 0;
}