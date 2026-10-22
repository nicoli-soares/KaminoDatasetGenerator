typedef struct {
    int n;
} CarRaceParams;

long long car_race_collision_c(CarRaceParams params) {
    return (long long)params.n * params.n;
}

void test_car_race_collision(void) {
    assert(car_race_collision_c((CarRaceParams){2}) == 4);
    assert(car_race_collision_c((CarRaceParams){3}) == 9);
    assert(car_race_collision_c((CarRaceParams){4}) == 16);
    assert(car_race_collision_c((CarRaceParams){8}) == 64);
    assert(car_race_collision_c((CarRaceParams){10}) == 100);
}

int main() {
    test_car_race_collision();
    return 0;
}