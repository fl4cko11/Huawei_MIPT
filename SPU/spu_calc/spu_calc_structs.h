#ifndef SPU_CALC_STRUCTS_H
#define SPU_CALC_STRUCTS_H

#include "/home/vlados/GitRepos/Huawei/stack_int/stack_int_funcs.h"

const int num_of_registers = 4;
const int RAM_size = 10;

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
    dump = 11,
    jump = 12,
    ja = 13,
    jae = 14,
    jb = 15,
    jbe = 16,
    je = 17,
    jne = 18,
    pop = 19,
    call = 20,
    cmd_return = 21,
    start = 22
} my_machine_code;

typedef struct {
    int *code_buffer;
    size_t size_cb;
    int ip;
    my_stack stk;
    my_stack stk_func;
    stackelem_t *regist;
    char *logname;
    stackelem_t *RAM;
} my_SPU;

#endif