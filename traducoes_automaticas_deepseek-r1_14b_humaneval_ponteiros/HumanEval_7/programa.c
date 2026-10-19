typedef struct {
    const char *str;
} StringElement;

int filter_by_substring_c(const char *input[], int n, const char *substring, char output[][256], int output_size, int *output_count) {
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (strstr(input[i], substring) != NULL) {
            if (count >= output_size) {
                return -1; // Buffer overflow
            }
            strcpy(output[count], input[i]);
            count++;
        }
    }
    
    *output_count = count;
    return 0;
}

void test_filter_by_substring_c() {
    const char *input1[] = {};
    const char *input2[] = {"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"};
    const char *input3[] = {"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"};
    const char *input4[] = {"grunt", "trumpet", "prune", "gruesome"};
    
    char output1[1][256];
    char output2[6][256];
    char output3[6][256];
    char output4[4][256];
    
    int output_count;
    
    assert(filter_by_substring_c(input1, 0, "a", output1, 1, &output_count) == 0);
    assert(output_count == 0);
    
    assert(filter_by_substring_c(input2, 6, "xxx", output2, 6, &output_count) == 0);
    assert(output_count == 3);
    assert(strcmp(output2[0], "xxx") == 0);
    assert(strcmp(output2[1], "xxxAAA") == 0);
    assert(strcmp(output2[2], "xxx") == 0);
    
    assert(filter_by_substring_c(input3, 6, "xx", output3, 6, &output_count) == 0);
    assert(output_count == 4);
    assert(strcmp(output3[0], "xxx") == 0);
    assert(strcmp(output3[1], "aaaxxy") == 0);
    assert(strcmp(output3[2], "xxxAAA") == 0);
    assert(strcmp(output3[3], "xxx") == 0);
    
    assert(filter_by_substring_c(input4, 4, "run", output4, 4, &output_count) == 0);
    assert(output_count == 2);
    assert(strcmp(output4[0], "grunt") == 0);
    assert(strcmp(output4[1], "prune") == 0);
}

int main() {
    test_filter_by_substring_c();
    return 0;
}