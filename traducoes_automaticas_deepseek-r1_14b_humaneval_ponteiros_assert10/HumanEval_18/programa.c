typedef struct {
    const char *original;
    const char *sub;
    size_t orig_len;
    size_t sub_len;
} StrPair;

static int how_many_times_c(const StrPair *pair) {
    int count = 0;
    int max_i = pair->orig_len - pair->sub_len;
    if (max_i < 0) {
        return 0;
    }
    for (int i = 0; i <= max_i; i++) {
        int match = 1;
        for (size_t j = 0; j < pair->sub_len; j++) {
            if (pair->original[i + j] != pair->sub[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            count++;
        }
    }
    return count;
}

static void test_case_1() {
    StrPair pair = {"", "x", 0, 1};
    int result = how_many_times_c(&pair);
    assert(result == 0);
}

static void test_case_2() {
    StrPair pair = {"xyxyxyx", "x", 7, 1};
    int result = how_many_times_c(&pair);
    assert(result == 4);
}

static void test_case_3() {
    StrPair pair = {"cacacacac", "cac", 9, 3};
    int result = how_many_times_c(&pair);
    assert(result == 4);
}

static void test_case_4() {
    StrPair pair = {"john doe", "john", 8, 4};
    int result = how_many_times_c(&pair);
    assert(result == 1);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}