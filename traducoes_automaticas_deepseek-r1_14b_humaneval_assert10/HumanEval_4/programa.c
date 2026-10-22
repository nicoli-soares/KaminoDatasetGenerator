#include <math.h>
#include <assert.h>

float mean_absolute_deviation_c(float numbers[], size_t length) {
    double sum = 0.0;
    for (size_t i = 0; i < length; ++i) {
        sum += numbers[i];
    }
    double mean = sum / length;
    double mad_sum = 0.0;
    for (size_t i = 0; i < length; ++i) {
        mad_sum += fabs(numbers[i] - mean);
    }
    return mad_sum / length;
}

void test1() {
    float numbers[] = {1.0f, 2.0f, 3.0f};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    assert(fabs(mean_absolute_deviation_c(numbers, length) - (2.0f/3.0f)) < 1e-6);
}

void test2() {
    float numbers[] = {1.0f, 2.0f, 3.0f, 4.0f};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    assert(fabs(mean_absolute_deviation_c(numbers, length) - 1.0f) < 1e-6);
}

void test3() {
    float numbers[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    assert(fabs(mean_absolute_deviation_c(numbers, length) - 6.0f/5.0f) < 1e-6);
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}