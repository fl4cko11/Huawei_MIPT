#ifndef STACK_DOUBLE_HASH_H
#define STACK_DOUBLE_HASH_H

#include "stack_double_structs.h"

unsigned long djb2_struct(my_stack *stk);

unsigned long djb2_data(my_stack *stk);

void djb2_stk(my_stack *stk);

#endif