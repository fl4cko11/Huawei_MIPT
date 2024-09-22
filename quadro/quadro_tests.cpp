#include "solver.h"
#include "in_out.h"

void test_two_roots() {
    coefs test_coefs = {1, -3, 2}; // x^2 - 3x + 2 = 0, roots: 2, 1
    roots result = quadro_solution(test_coefs);
    assert(result.root1 == 2);
    assert(result.root2 == 1);
}

void test_one_root() {
    coefs test_coefs = {1, 2, 1}; // x^2 + 2x + 1 = 0, roots: -1, -1
    roots result = quadro_solution(test_coefs);
    assert(result.root1 == -1);
    assert(isnan(result.root2));
}

void test_no_roots() {
    coefs test_coefs = {1, 0, 1}; // x^2 + 1 = 0, no roots
    roots result = quadro_solution(test_coefs);
    assert(isnan(result.root1));
    assert(isnan(result.root2));
}

void test_linear_equation() {
    coefs test_coefs = {0, 2, -4}; // 2x - 4 = 0, root: 2
    roots result = quadro_solution(test_coefs);
    assert(result.root1 == 2);
    assert(isnan(result.root2));
}

void test_all_zeroes() {
    coefs test_coefs = {0, 0, 0}; // 0x = 0, no roots (program logic)
    roots result = quadro_solution(test_coefs);
    assert(isnan(result.root1));
    assert(isnan(result.root2));
}

int main() {
    test_two_roots();
    test_one_root();
    test_no_roots();
    test_linear_equation();
    test_all_zeroes();

    printf("All tests passed!\n");
    return 0;
}