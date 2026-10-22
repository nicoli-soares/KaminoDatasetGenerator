#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
    int* factors;
    int count;
} FactorResult;

FactorResult factorize_c(int n) {
    int* factors = (int*)malloc(1 * sizeof(int));
    int count = 0;
    int i;
    if (n == 1) {
        return (FactorResult){NULL, 0};
    }
    for (i = 2; i <= (int)sqrt(n) + 1; i++) {
        while (n % i == 0) {
            factors = (int*)realloc(factors, (count + 1) * sizeof(int));
            factors[count++] = i;
            n /= i;
        }
    }
    if (n > 1) {
        factors = (int*)realloc(factors, (count + 1) * sizeof(int));
        factors[count++] = n;
    }
    return (FactorResult){factors, count};
}

void check(int* (*candidate)(int)) {
    FactorResult result;
    
    result = candidate(2);
    assert(result.count == 1);
    assert(result.factors[0] == 2);
    
    result = candidate(4);
    assert(result.count == 2);
    assert(result.factors[0] == 2);
    assert(result.factors[1] == 2);
    
    result = candidate(8);
    assert(result.count == 3);
    assert(result.factors[0] == 2);
    assert(result.factors[1] == 2);
    assert(result.factors[2] == 2);
    
    result = candidate(3*19);
    assert(result.count == 2);
    assert(result.factors[0] == 3);
    assert(result.factors[1] == 19);
    
    result = candidate(3*19*3*19);
    assert(result.count == 4);
    assert(result.factors[0] == 3);
    assert(result.factors[1] == 3);
    assert(result.factors[2] == 19);
    assert(result.factors[3] == 19);
    
    result = candidate(3*19*19*19);
    assert(result.count == 4);
    assert(result.factors[0] == 3);
    assert(result.factors[1] == 19);
    assert(result.factors[2] == 19);
    assert(result.factors[3] == 19);
    
    result = candidate(3*2*3);
    assert(result.count == 3);
    assert(result.factors[0] == 2);
    assert(result.factors[1] == 3);
    assert(result.factors[2] == 3);
}

int main() {
    check(factorize_c);
    return 0;
}