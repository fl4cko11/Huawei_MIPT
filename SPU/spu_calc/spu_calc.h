#ifndef SPU_CALC_H
#define SPU_CALC_H

#include <ctype.h>
#include "spu_calc_structs.h"

size_t number_of_int_in_file(FILE *fp);

void spu_code_buffer_ctor(char *pathname, my_SPU *spu, FILE *log_file);

void spu_ctor(my_SPU *spu, char *codefilename, char *logname);

void spu_dump(my_SPU *spu);

void run(char *codefilename, char *logname);

#endif