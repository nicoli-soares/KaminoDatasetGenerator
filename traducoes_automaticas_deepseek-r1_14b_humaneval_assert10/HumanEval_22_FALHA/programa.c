typedef enum {
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_STRING,
    VALUE_OTHER
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_val;
        double float_val;
        char *string_val;
    } value;
} ValueElement;

int* filter_integers_c(int num_elements, const ValueElement *elements, int *result_size) {
    int *result = NULL;
    *result_size = 0;

    for (int i = 0; i < num_elements; i++) {
        if (elements[i].type == VALUE_INT) {
            result = realloc(result, (*result_size + 1) * sizeof(int));
            result[*result_size] = elements[i].value.int_val;
            (*result_size)++;
        }
    }

    return result;
}

int main() {
    // Test case 1: empty list
    ValueElement empty_list[] = {};
    int result_size;
    int *result = filter_integers_c(0, NULL, &result_size);
    assert(result_size == 0);
    free(result);

    // Test case 2: [4, {}, [], 23.2, 9, 'adasd']
    ValueElement test2[] = {
        {VALUE_INT, .int_val = 4},
        {VALUE_OTHER, .int_val = 0},
        {VALUE_OTHER, .int_val = 0},
        {VALUE_FLOAT, .float_val = 23.2},
        {VALUE_INT, .int_val = 9},
        {VALUE_STRING, .string_val = "adasd"},
    };
    int result_size_test2;
    int *result_test2 = filter_integers_c(6, test2, &result_size_test2);
    assert(result_size_test2 == 2);
    assert(result_test2[0] == 4);
    assert(result_test2[1] == 9);
    free(result_test2);

    // Test case 3: [3, 'c', 3, 3, 'a', 'b']
    ValueElement test3[] = {
        {VALUE_INT, .int_val = 3},
        {VALUE_STRING, .string_val = "c"},
        {VALUE_INT, .int_val = 3},
        {VALUE_INT, .int_val = 3},
        {VALUE_STRING, .string_val = "a"},
        {VALUE_STRING, .string_val = "b"},
    };
    int result_size_test3;
    int *result_test3 = filter_integers_c(6, test3, &result_size_test3);
    assert(result_size_test3 == 3);
    assert(result_test3[0] == 3);
    assert(result_test3[1] == 3);
    assert(result_test3[2] == 3);
    free(result_test3);

    return 0;
}