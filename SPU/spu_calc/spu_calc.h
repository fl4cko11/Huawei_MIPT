#ifndef SPU_CALC_H
#define SPU_CALC_H

#include <ctype.h>
#include "spu_calc_structs.h"

void spu_code_buffer_ctor(char *pathname, my_SPU *spu);

void run(char *argv);

#endif