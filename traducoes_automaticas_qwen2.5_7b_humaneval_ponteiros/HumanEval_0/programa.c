#include <assert.h>
#include <math.h>

typedef struct {
    float number;
} Number;

typedef struct {
    Number numbers[1000];
    int size;
} Numbers;

int has_close_elements_c(const Numbers *numbers, float threshold) {
    int size = numbers->size;
    for (int idx = 0; idx < size; idx++) {
        for (int idx2 = 0; idx2 < size; idx2++) {
            if (idx != idx2) {
                float distance = fabs(numbers->numbers[idx].number - numbers->numbers[idx2].number);
                if (distance < threshold) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    Numbers nums1 = {{1.0, 2.0, 3.9, 4.0, 5.0, 2.2}, 6};
    assert(has_close_elements_c(&nums1, 0.3) == 1);
    assert(has_close_elements_c(&nums1, 0.05) == 0);

    Numbers nums2 = {{1.0, 2.0, 5.9, 4.0, 5.0}, 5};
    assert(has_close_elements_c(&nums2, 0.95) == 1);
    assert(has_close_elements_c(&nums2, 0.8) == 0);

    Numbers nums3 = {{1.0, 2.0, 3.0, 4.0, 5.0, 2.0}, 6};
    assert(has_close_elements_c(&nums3, 0.1) == 1);

    Numbers nums4 = {{1.1, 2.2, 3.1, 4.1, 5.1}, 5};
    assert(has_close_elements_c(&nums4, 1.0) == 1);
    assert(has_close_elements_c(&nums4, 0.5) == 0);

    return 0;
}