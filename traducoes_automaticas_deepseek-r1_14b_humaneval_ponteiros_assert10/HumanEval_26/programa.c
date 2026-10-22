typedef struct {
    int key;
    int count;
} ElementCount;

int remove_duplicates_c(int input[], int n, int output[]) {
    ElementCount counts[1000];  // Using a fixed-size array for demonstration
    int count_size = 0;

    // First pass: count occurrences
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < count_size; j++) {
            if (counts[j].key == input[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (count_size >= 1000) {
                return -1; // Handle overflow by returning error
            }
            counts[count_size].key = input[i];
            counts[count_size].count = 1;
            count_size++;
        }
    }

    // Second pass: build output
    int output_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < count_size; j++) {
            if (counts[j].key == input[i] && counts[j].count == 1) {
                output[output_index] = input[i];
                output_index++;
                break;
            }
        }
    }

    return output_index;
}

void test_remove_duplicates_1() {
    int output[1000];
    int input[0];  // Declare an empty array
    assert(remove_duplicates_c(input, 0, output) == 0);
}

void test_remove_duplicates_2() {
    int input[] = {1, 2, 3, 4};
    int output[1000];
    int result = remove_duplicates_c(input, 4, output);
    assert(result == 4);
    assert(output[0] == 1);
    assert(output[1] == 2);
    assert(output[2] == 3);
    assert(output[3] == 4);
}

void test_remove_duplicates_3() {
    int input[] = {1, 2, 3, 2, 4, 3, 5};
    int output[1000];
    int result = remove_duplicates_c(input, 7, output);
    assert(result == 3);
    assert(output[0] == 1);
    assert(output[1] == 4);
    assert(output[2] == 5);
}

int main() {
    int output[1000];
    
    test_remove_duplicates_1();
    test_remove_duplicates_2();
    test_remove_duplicates_3();
    
    return 0;
}