#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double *rescale_to_unit_c(double *numbers, int n, double *result) {
    double min_num = numbers[0];
    double max_num = numbers[0];

    for (int i = 0; i < n; i++) {
        if (numbers[i] < min_num) {
            min_num = numbers[i];
        }
        if (numbers[i] > max_num) {
            max_num = numbers[i];
        }
    }

    if (min_num == max_num) {
        for (int i = 0; i < n; i++) {
            result[i] = 0.0;
        }
    } else {
        for (int i = 0; i < n; i++) {
            result[i] = (numbers[i] - min_num) / (max_num - min_num);
        }
    }

    return result;
}

int main() {
    // Test case 1
    double input1[] = {2.0, 49.9};
    int n1 = sizeof(input1)/sizeof(input1[0]);
    double *output1 = malloc(n1 * sizeof(double));
    rescale_to_unit_c(input1, n1, output1);
    assert(fabs(output1[0] - 0.0) < 1e-6 && fabs(output1[1] - 1.0) < 1e-6);
    
    // Test case 2
    double input2[] = {100.0, 49.9};
    int n2 = sizeof(input2)/sizeof(input2[0]);
    double *output2 = malloc(n2 * sizeof(double));
    rescale_to_unit_c(input2, n2, output2);
    assert(fabs(output2[0] - 1.0) < 1e-6 && fabs(output2[1] - 0.0) < 1e-6);
    
    // Test case 3
    double input3[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int n3 = sizeof(input3)/sizeof(input3[0]);
    double *output3 = malloc(n3 * sizeof(double));
    rescale_to_unit_c(input3, n3, output3);
    assert(fabs(output3[0] - 0.0) < 1e-6 && fabs(output3[1] - 0.25) < 1e-6 && 
           fabs(output3[2] - 0.5) < 1e-6 && fabs(output3[3] - 0.75) < 1e-6 && 
           fabs(output3[4] - 1.0) < 1e-6);
    
    // Test case 4
    double input4[] = {2.0, 1.0, 5.0, 3.0, 4.0};
    int n4 = sizeof(input4)/sizeof(input4[0]);
    double *output4 = malloc(n4 * sizeof(double));
    rescale_to_unit_c(input4, n4, output4);
    assert(fabs(output4[0] - 0.25) < 1e-6 && fabs(output4[1] - 0.0) < 1e-6 && 
           fabs(output4[2] - 1.0) < 1e-6 && fabs(output4[3] - 0.5) < 1e-6 && 
           fabs(output4[4] - 0.75) < 1e-6);
    
    // Test case 5
    double input5[] = {12.0, 11.0, 15.0, 13.0, 14.0};
    int n5 = sizeof(input5)/sizeof(input5[0]);
    double *output5 = malloc(n5 * sizeof(double));
    rescale_to_unit_c(input5, n5, output5);
    assert(fabs(output5[0] - 0.25) < 1e-6 && fabs(output5[1] - 0.0) < 1e-6 && 
           fabs(output5[2] - 1.0) < 1e-6 && fabs(output5[3] - 0.5) < 1e-6 && 
           fabs(output5[4] - 0.75) < 1e-6);
    
    // Test case 6 - All elements the same
    double input6[] = {5.0, 5.0};
    int n6 = sizeof(input6)/sizeof(input6[0]);
    double *output6 = malloc(n6 * sizeof(double));
    rescale_to_unit_c(input6, n6, output6);
    assert(fabs(output6[0] - 0.0) < 1e-6 && fabs(output6[1] - 0.0) < 1e-6);
    
    free(output1);
    free(output2);
    free(output3);
    free(output4);
    free(output5);
    free(output6);
    
    return 0;
}