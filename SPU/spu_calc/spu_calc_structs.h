#ifndef SPU_CALC_STRUCTS_H
#define SPU_CALC_STRUCTS_H

#include "/home/vlados/GitRepos/Huawei/stack_int/stack_int_funcs.h"

typedef enum {
    hlt = 0,
    push = 1,
    add = 2,
    sub = 3,
    my_div = 4,
    mul = 5,
    my_sqrt = 6,
    my_sin = 7,
    my_cos = 8,
    out = 9,
    in = 10,
    dump = 11
} my_machine_code;

typedef struct {
    int *code_buffer;
    size_t size_cb;
} my_SPU;

#endif