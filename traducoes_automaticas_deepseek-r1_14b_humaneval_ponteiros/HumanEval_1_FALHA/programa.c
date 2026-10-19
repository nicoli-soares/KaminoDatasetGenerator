typedef struct {
    char str[256]; // tamanho suficiente para armazenar os grupos
    int len;
} StringGroup;

void separate_paren_groups_c(const char input[256], StringGroup output[16]) {
    int current_depth = 0;
    char current_string[256];
    int current_len = 0;
    int group_index = 0; // Indice para rastrear os grupos criados

    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        if (c == '(' || c == ')') {
            if (c == '(') {
                current_depth++;
                current_string[current_len++] = c;
            } else {
                current_depth--;
                current_string[current_len++] = c;

                if (current_depth == 0) {
                    // Adiciona o grupo atual ao array de saída
                    StringGroup *group = &output[group_index];
                    strncpy(group->str, current_string, current_len);
                    group->str[current_len] = '\0';
                    group->len = current_len;
                    current_len = 0;
                    group_index++;
                }
            }
        }
    }
}

// Funções de teste
void test_case_1() {
    const char input[256] = "(()()) ((())) () ((())()())";
    StringGroup output[16];
    separate_paren_groups_c(input, output);

    // Verifica os resultados
    assert(strcmp(output[0].str, "(()())") == 0);
    assert(strcmp(output[1].str, "((()))") == 0);
    assert(strcmp(output[2].str, "()") == 0);
    assert(strcmp(output[3].str, "((())()())") == 0);
}

void test_case_2() {
    const char input[256] = "() (()) ((())) (((())))";
    StringGroup output[16];
    separate_paren_groups_c(input, output);

    assert(strcmp(output[0].str, "()") == 0);
    assert(strcmp(output[1].str, "(())") == 0);
    assert(strcmp(output[2].str, "((()))") == 0);
    assert(strcmp(output[3].str, "((((())))") == 0);
}

void test_case_3() {
    const char input[256] = "(()(())((())))";
    StringGroup output[16];
    separate_paren_groups_c(input, output);

    assert(strcmp(output[0].str, "(()(())((())))") == 0);
}

void test_case_4() {
    const char input[256] = "( ) (( )) (( )( ))";
    StringGroup output[16];
    separate_paren_groups_c(input, output);

    assert(strcmp(output[0].str, "()") == 0);
    assert(strcmp(output[1].str, "(())") == 0);
    assert(strcmp(output[2].str, "(()())") == 0);
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    return 0;
}