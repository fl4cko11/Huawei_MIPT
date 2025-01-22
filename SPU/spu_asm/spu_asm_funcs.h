#ifndef SPU_ASM_FUNCS_H
#define SPU_ASM_FUNCS_H

#include "spu_asm_structs.h"

void lable_table_ctor(asm_lable_table *label_table, char *logname);

void lable_table_dump (asm_lable_table *label_table);

int label_to_ip(char *arg_of_cmd, asm_lable_table *label_table);

void print_to_asm_log (char *logname, char *cmd, char * command_part_of_cmd, char *arg_part_of_cmd, int ip_asm);

void ptr_in_cmd_to_arg(char *ptr_in_cmd, char *cmd);

int command_cmp_and_writer(char cmd[], FILE *program_code, asm_lable_table *label_table, int number_of_str);

#endif