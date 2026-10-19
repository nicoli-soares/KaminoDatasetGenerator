#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int value;
} IntValue;

typedef struct {
    int *elements;
    int size;
} IntList;

IntList *intersperse_c(int *numbers, int size, int delimiter) {
    if (size == 0) {
        return (IntList *) malloc(sizeof(IntList));
        ((IntList *) malloc(sizeof(IntList)))->size = 0;
        ((IntList *) malloc(sizeof(IntList)))->elements = NULL;
        return (IntList *) malloc(sizeof(IntList));
    }

    IntList *result = (IntList *) malloc(sizeof(IntList));
    result->size = 2 * size - 1;
    result->elements = (int *) malloc(result->size * sizeof(int));

    int index = 0;
    for (int i = 0; i < size - 1; i++) {
        result->elements[index++] = numbers[i];
        result->elements[index++] = delimiter;
    }
    result->elements[index] = numbers[size - 1];

    return result;
}

void free_int_list(IntList *list) {
    free(list->elements);
    free(list);
}

void test_intersperse_c() {
    IntList *result = intersperse_c(NULL, 0, 7);
    assert(result->size == 0);
    assert(result->elements == NULL);

    int numbers1[] = {5, 6, 3, 2};
    result = intersperse_c(numbers1, 4, 8);
    assert(result->size == 7);
    assert(result->elements[0] == 5);
    assert(result->elements[1] == 8);
    assert(result->elements[2] == 6);
    assert(result->elements[3] == 8);
    assert(result->elements[4] == 3);
    assert(result->elements[5] == 8);
    assert(result->elements[6] == 2);
    free_int_list(result);

    int numbers2[] = {2, 2, 2};
    result = intersperse_c(numbers2, 3, 2);
    assert(result->size == 5);
    assert(result->elements[0] == 2);
    assert(result->elements[1] == 2);
    assert(result->elements[2] == 2);
    assert(result->elements[3] == 2);
    assert(result->elements[4] == 2);
    free_int_list(result);
}

int main() {
    test_intersperse_c();
    return 0;
}