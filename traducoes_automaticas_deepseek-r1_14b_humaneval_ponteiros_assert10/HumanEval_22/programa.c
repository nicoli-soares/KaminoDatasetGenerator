typedef enum {
    NONE,
    INT,
    FLOAT,
    STRING,
    BOOL,
    OBJECT,
    ARRAY,
    DICT
} Type;

typedef struct {
    Type type;
    int integer_value;
    double float_value;
    char *string_value;
} Value;

int filter_integers_c(Value *values, int n, int *result, int *result_size) {
    *result_size = 0;
    for (int i = 0; i < n; i++) {
        if (values[i].type == INT && values[i].integer_value != 0 && values[i].integer_value != 1) {
            result[(*result_size)++] = values[i].integer_value;
        }
    }
    return 0;
}

void test_case_1() {
    Value input[] = { {NONE, 0, 0, NULL} };
    int result[1];
    int size;
    filter_integers_c(input, 1, result, &size);
    assert(size == 0);
}

void test_case_2() {
    Value input[] = {
        {INT, 4, 0, NULL},
        {DICT, 0, 0, NULL},
        {ARRAY, 0, 0, NULL},
        {FLOAT, 0, 23.2, NULL},
        {INT, 9, 0, NULL},
        {STRING, 0, 0, "adasd"}
    };
    int result[6];
    int size;
    filter_integers_c(input, 6, result, &size);
    int expected[] = {4, 9};
    assert(size == 2 && result[0] == 4 && result[1] == 9);
}

void test_case_3() {
    Value input[] = {
        {INT, 3, 0, NULL},
        {STRING, 0, 0, "c"},
        {INT, 3, 0, NULL},
        {INT, 3, 0, NULL},
        {STRING, 0, 0, "a"},
        {STRING, 0, 0, "b"}
    };
    int result[6];
    int size;
    filter_integers_c(input, 6, result, &size);
    int expected[] = {3, 3, 3};
    assert(size == 3 && result[0] == 3 && result[1] == 3 && result[2] == 3);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}