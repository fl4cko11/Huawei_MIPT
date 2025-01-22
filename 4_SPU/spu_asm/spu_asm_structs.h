#ifndef SPU_ASM_STRUCTS_H
#define SPU_ASM_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int num_of_labels = 15;
const int max_len_of_label = 10;

typedef struct {
    char *name;
    int ip;
} spu_label;

typedef struct {
    spu_label *label;
    size_t size;
    char *logname;
} asm_lable_table;

#endif