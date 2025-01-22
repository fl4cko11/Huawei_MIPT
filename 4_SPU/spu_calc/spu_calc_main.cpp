#include "spu_calc_funcs.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <full path to code_file> <full path to log_file>\n", argv[0]);
        return 1;
    } 
    run(argv[1], argv[2]);
    return 0;
}