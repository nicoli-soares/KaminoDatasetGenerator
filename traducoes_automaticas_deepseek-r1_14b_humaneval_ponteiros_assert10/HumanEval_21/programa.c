typedef struct {
    double number;
} NumberData;

double rescale_to_unit_c(double input[], int size) {
    double min = input[0];
    double max = input[0];
    
    for (int i = 0; i < size; i++) {
        if (input[i] < min) {
            min = input[i];
        }
        if (input[i] > max) {
            max = input[i];
        }
    }
    
    double result[size];
    for (int i = 0; i < size; i++) {
        result[i] = (input[i] - min) / (max - min);
    }
    
    return result[0];
}

void test_rescale_to_unit_c() {
    double test1_input[] = {2.0, 49.9};
    double test1_expected[] = {0.0, 1.0};
    assert(fabs(rescale_to_unit_c(test1_input, 2) - test1_expected[0]) < 1e-6);

    double test2_input[] = {100.0, 49.9};
    double test2_expected[] = {1.0, 0.0};
    assert(fabs(rescale_to_unit_c(test2_input, 2) - test2_expected[0]) < 1e-6);

    double test3_input[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double test3_expected[] = {0.0, 0.25, 0.5, 0.75, 1.0};
    assert(fabs(rescale_to_unit_c(test3_input, 5) - test3_expected[0]) < 1e-6);

    double test4_input[] = {2.0, 1.0, 5.0, 3.0, 4.0};
    double test4_expected[] = {0.25, 0.0, 1.0, 0.5, 0.75};
    assert(fabs(rescale_to_unit_c(test4_input, 5) - test4_expected[0]) < 1e-6);

    double test5_input[] = {12.0, 11.0, 15.0, 13.0, 14.0};
    double test5_expected[] = {0.25, 0.0, 1.0, 0.5, 0.75};
    assert(fabs(rescale_to_unit_c(test5_input, 5) - test5_expected[0]) < 1e-6);
}

int main() {
    test_rescale_to_unit_c();
    return 0;
}