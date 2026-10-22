typedef struct {
    int chave;
    int valor;
} ChaveValor;

int rolling_max_c(int nums[], int n, int result[]) {
    if (n == 0) {
        return -1; // Indica que nenhuma operacao foi feita
    }
    
    int running_max = nums[0];
    result[0] = running_max;

    for (int i = 1; i < n; i++) {
        if (nums[i] > running_max) {
            running_max = nums[i];
        }
        result[i] = running_max;
    }
    
    return 0; // Sucesso
}

void test_rolling_max_c_vazio() {
    int nums[] = {};
    int result[1] = {};
    int status = rolling_max_c(nums, 0, result);
    assert(status == -1);
}

void test_rolling_max_c_crescente() {
    int nums[] = {1, 2, 3, 4};
    int result[4] = {};
    int status = rolling_max_c(nums, 4, result);
    assert(status == 0);
    assert(result[0] == 1);
    assert(result[1] == 2);
    assert(result[2] == 3);
    assert(result[3] == 4);
}

void test_rolling_max_c_decreasing() {
    int nums[] = {4, 3, 2, 1};
    int result[4] = {};
    int status = rolling_max_c(nums, 4, result);
    assert(status == 0);
    assert(result[0] == 4);
    assert(result[1] == 4);
    assert(result[2] == 4);
    assert(result[3] == 4);
}

void test_rolling_max_c_subir_descer() {
    int nums[] = {3, 2, 3, 100, 3};
    int result[5] = {};
    int status = rolling_max_c(nums, 5, result);
    assert(status == 0);
    assert(result[0] == 3);
    assert(result[1] == 3);
    assert(result[2] == 3);
    assert(result[3] == 100);
    assert(result[4] == 100);
}

int main() {
    test_rolling_max_c_vazio();
    test_rolling_max_c_crescente();
    test_rolling_max_c_decreasing();
    test_rolling_max_c_subir_descer();
    return 0;
}