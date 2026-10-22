#include <math.h>

typedef struct {
    float first;
    float second;
} Pair;

Pair find_closest_elements(float numbers[], int length) {
    Pair closest_pair;
    float min_distance = FLT_INFINITY; // Initialize with a very large value

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (i != j) {
                float current_distance = fabs(numbers[i] - numbers[j]);
                Pair current_pair = {numbers[i], numbers[j]};

                // Ensure the pair is stored in order
                if (current_pair.first > current_pair.second) {
                    float temp = current_pair.first;
                    current_pair.first = current_pair.second;
                    current_pair.second = temp;
                }

                if (current_distance < min_distance) {
                    min_distance = current_distance;
                    closest_pair = current_pair;
                }
            }
        }
    }

    return closest_pair;
}

int main() {
    // Test cases
    assert(find_closest_elements((float[]){1.0, 2.0, 3.9, 4.0, 5.0, 2.2}, 6).first == 3.9 && 
           find_closest_elements((float[]){1.0, 2.0, 3.9, 4.0, 5.0, 2.2}, 6).second == 4.0);
    assert(find_closest_elements((float[]){1.0, 2.0, 5.9, 4.0, 5.0}, 5).first == 5.0 && 
           find_closest_elements((float[]){1.0, 2.0, 5.9, 4.0, 5.0}, 5).second == 5.9);
    assert(find_closest_elements((float[]){1.0, 2.0, 3.0, 4.0, 5.0, 2.2}, 6).first == 2.0 && 
           find_closest_elements((float[]){1.0, 2.0, 3.0, 4.0, 5.0, 2.2}, 6).second == 2.2);
    assert(find_closest_elements((float[]){1.0, 2.0, 3.0, 4.0, 5.0, 2.0}, 6).first == 2.0 && 
           find_closest_elements((float[]){1.0, 2.0, 3.0, 4.0, 5.0, 2.0}, 6).second == 2.0);
    assert(find_closest_elements((float[]){1.1, 2.2, 3.1, 4.1, 5.1}, 5).first == 2.2 && 
           find_closest_elements((float[]){1.1, 2.2, 3.1, 4.1, 5.1}, 5).second == 3.1);

    return 0;
}