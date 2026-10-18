typedef struct {
    double number;
} Numero;

double truncate_number(double number) {
    return fmod(number, 1.0);
}

void test_check() {
    if (truncate_number(3.5) != 0.5) {
        exit(1);
    }
    double result = truncate_number(1.33);
    if (fabs(result - 0.33) >= 1e-6) {
        exit(1);
    }
    result = truncate_number(123.456);
    if (fabs(result - 0.456) >= 1e-6) {
        exit(1);
    }
}

int main() {
    test_check();
    return 0;
}