#include "solver.h"
#include "in_out.h"

bool is_equal(roots *exp_roots, roots *res_roots) {
    bool flag1 = isnan(res_roots->root1) ? isnan(exp_roots->root1) || isnan(exp_roots->root2) : 
                (res_roots->root1 == exp_roots->root1 || res_roots->root1 == exp_roots->root2);
    bool flag2 = isnan(res_roots->root2) ? isnan(exp_roots->root1) || isnan(exp_roots->root2) : 
                (res_roots->root2 == exp_roots->root1 || res_roots->root2 == exp_roots->root2);
    return flag1 && flag2;
}

int run_test(roots exp_roots, roots res_roots, const char *test_name) {
    if (!is_equal(&exp_roots, &res_roots)) {
        printf("%s - failed\n expected roots: %f, %f\n result roots (NAN <=> no roots): %f, %f\n\n",
               test_name, exp_roots.root1, exp_roots.root2, res_roots.root1, res_roots.root2);
        return 0;
    }
    return 1;
}

int main() {
    int passed = 1;

    coefs coef1 = {1, -3, 2};
    coefs coef2 = {1, 2, 1};
    coefs coef3 = {1, 0, 1};
    coefs coef4 = {0, 2, -4};
    coefs coef5 = {1, 2.000000000000000001, 1};

    quadro_tests tests[] = {
        {{2, 1}, quadro_solution(&coef1)},          // Two roots
        {{-1, NAN}, quadro_solution(&coef2)},       // One root
        {{NAN, NAN}, quadro_solution(&coef3)},      // No roots
        {{2, NAN}, quadro_solution(&coef4)},         // Linear equation
        {{-1, NAN}, quadro_solution(&coef5)}          // Little coefficients
    };

    const char *test_names[] = {
        "test_two_roots",
        "test_one_root",
        "test_no_roots",
        "test_linear_equation",
        "test_little_coefs"
    };

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
        passed &= run_test(tests[i].exp_roots, tests[i].res_roots, test_names[i]);
    }

    if (passed) {
        printf("All tests passed!\n");
    }

    return 0;
}