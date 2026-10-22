double truncate_number(double number) {
    return fmod(number, 1.0);
}

void check(double (*candidate)(double)) {
    double result;
    result = candidate(3.5);
    assert(result == 0.5);
    result = candidate(1.33);
    assert(fabs(result - 0.33) < 1e-6);
    result = candidate(123.456);
    assert(fabs(result - 0.456) < 1e-6);
}

int main() {
    check(truncate_number);
    return 0;
}