typedef struct {
    char *str;
} StrHelper;

StrHelper flip_case_c(StrHelper input) {
    int length = strlen(input.str);
    char output[length + 1];
    int i;
    for (i = 0; i < length; i++) {
        if (islower(input.str[i])) {
            output[i] = toupper(input.str[i]);
        } else if (isupper(input.str[i])) {
            output[i] = tolower(input.str[i]);
        } else {
            output[i] = input.str[i];
        }
    }
    output[i] = '\0';
    return (StrHelper){output};
}

void test_flip_case_1() {
    StrHelper input = {"Hello!"};
    StrHelper result = flip_case_c(input);
    assert(strcmp(result.str, "hELLO!") == 0);
}

void test_flip_case_2() {
    StrHelper input = {"These violent delights have violent ends"};
    StrHelper result = flip_case_c(input);
    assert(strcmp(result.str, "tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS") == 0);
}

int main() {
    test_flip_case_1();
    test_flip_case_2();
    return 0;
}