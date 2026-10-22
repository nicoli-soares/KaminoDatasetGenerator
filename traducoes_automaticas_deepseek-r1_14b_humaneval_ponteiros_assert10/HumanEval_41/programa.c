typedef struct {
    int n;
} CarRaceParams;

int car_race_collision(int n) {
    return n * n;
}

void test_case_2() {
    assert(car_race_collision(2) == 4);
}

void test_case_3() {
    assert(car_race_collision(3) == 9);
}

void test_case_4() {
    assert(car_race_collision(4) == 16);
}

void test_case_8() {
    assert(car_race_collision(8) == 64);
}

void test_case_10() {
    assert(car_race_collision(10) == 100);
}

int main() {
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_8();
    test_case_10();
    return 0;
}