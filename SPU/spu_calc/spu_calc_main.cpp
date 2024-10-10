#include "spu_calc.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <full path to code_file> <full path to log_stk_file>\n", argv[0]);
        return 1;
    } 
    run(argv[1], argv[2]);
    return 0;
}