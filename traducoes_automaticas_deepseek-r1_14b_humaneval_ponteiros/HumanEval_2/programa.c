double truncate_number(double number) {
    return fmod(number, 1.0);
}

void test_truncate_number() {
    assert(truncate_number(3.5) == 0.5);
    assert(fabs(truncate_number(1.33) - 0.33) < 1e-6);
    assert(fabs(truncate_number(123.456) - 0.456) < 1e-6);
}

int main() {
    test_truncate_number();
    return 0;
}