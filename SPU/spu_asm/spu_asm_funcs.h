#ifndef SPU_ASM_FUNCS_H
#define SPU_ASM_FUNCS_H

#include "spu_asm_structs.h"

void lable_table_ctor(asm_lable_table *label_table, char *logname);

void lable_table_dump (asm_lable_table *label_table);

int command_cmp_and_writer(char cmd[], FILE *program_code, asm_lable_table *label_table, int number_of_str);

#endif