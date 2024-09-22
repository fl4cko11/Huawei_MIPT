#include "solver.h"
#include "in_out.h"

int main() {
    coefs coefs = quadro_input();
    roots roots = quadro_solution(&coefs);
    quadro_output(&roots);
    return 0;
}