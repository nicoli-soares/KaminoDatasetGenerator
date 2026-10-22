typedef struct {
    int* elements;
    int size;
} ListStruct;

int max_element(ListStruct* list) {
    if (list->size == 0) {
        return -1; // Assuming empty list is handled, but per problem statement, input is always valid
    }
    int max = list->elements[0];
    for (int i = 0; i < list->size; i++) {
        if (list->elements[i] > max) {
            max = list->elements[i];
        }
    }
    return max;
}

// Test cases
void test_max_element() {
    ListStruct test1 = { (int[]){1, 2, 3}, 3 };
    assert(max_element(&test1) == 3);

    ListStruct test2 = { (int[]){5, 3, -5, 2, -3, 3, 9, 0, 124, 1, -10}, 11 };
    assert(max_element(&test2) == 124);
}

int main() {
    test_max_element();
    return 0;
}