#include <math.h>

double truncate_number_c(double number) {
    return fmod(number, 1.0);
}

void test1() {
    double result = truncate_number_c(3.5);
    assert(fabs(result - 0.5) < 1e-6);
}

void test2() {
    double result = truncate_number_c(1.33);
    assert(fabs(result - 0.33) < 1e-6);
}

void test3() {
    double result = truncate_number_c(123.456);
    assert(fabs(result - 0.456) < 1e-6);
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}