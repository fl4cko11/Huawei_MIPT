#include <stdio.h>
#include "solver.h"

bool is_equal(const double d1, const double d2) {
    if (isnan(d1) && isnan(d2)) {
        return 1;
    }
    else if ( (isnan(d1) && !isnan(d2)) || (!isnan (d1) && isnan(d2)) ) {
        return 0;
    }
    else if (d1 == d2) {
        return 1;
    }
    else return 0; 
}

int main() {
    int passed = 0;
    quadro_tests tests[] = {
        {{1, -3, 2}, {2, 1}, "test_two_roots"},
        {{1, 2, 1}, {-1, NAN}, "test_one_root"},
        {{1, 0, 1}, {NAN, NAN}, "test_no_roots"},
        {{0, 2, -4}, {2, NAN}, "test_linear_equation"},
        {{1, 2.000000000000000001, 1}, {-1, NAN}, "test_little_coefs"}
    };
    
    roots roots = {};
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        roots = quadro_solution(&tests[i].test_coefs);
        if ( (is_equal(tests[i].exp_roots.root1, roots.root1) || is_equal(tests[i].exp_roots.root1, roots.root2)) && (is_equal(tests[i].exp_roots.root2, roots.root1) || is_equal(tests[i].exp_roots.root2, roots.root2))) {
            printf("test %s good!\n", tests[i].testname);
            passed++;
        }
        else printf("test %s went wrong!\n", tests[i].testname);
    }
    printf ("passed count: %d\n", passed);
    return 0;
}