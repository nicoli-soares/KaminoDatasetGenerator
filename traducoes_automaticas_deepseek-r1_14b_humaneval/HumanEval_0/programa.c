int has_close_elements_c(double numbers[], int length, double threshold) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (i != j) {
                double distance = fabs(numbers[i] - numbers[j]);
                if (distance < threshold) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void test_has_close_elements_c() {
    assert(has_close_elements_c((double[]){1.0, 2.0, 3.9, 4.0, 5.0, 2.2}, 6, 0.3) == 1);
    assert(has_close_elements_c((double[]){1.0, 2.0, 3.9, 4.0, 5.0, 2.2}, 6, 0.05) == 0);
    assert(has_close_elements_c((double[]){1.0, 2.0, 5.9, 4.0, 5.0}, 5, 0.95) == 1);
    assert(has_close_elements_c((double[]){1.0, 2.0, 5.9, 4.0, 5.0}, 5, 0.8) == 0);
    assert(has_close_elements_c((double[]){1.0, 2.0, 3.0, 4.0, 5.0, 2.0}, 6, 0.1) == 1);
    assert(has_close_elements_c((double[]){1.1, 2.2, 3.1, 4.1, 5.1}, 5, 1.0) == 1);
    assert(has_close_elements_c((double[]){1.1, 2.2, 3.1, 4.1, 5.1}, 5, 0.5) == 0);
}

int main() {
    test_has_close_elements_c();
    return 0;
}