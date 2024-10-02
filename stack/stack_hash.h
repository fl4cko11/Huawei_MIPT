#ifndef STACK_HASH_H
#define STACK_HASH_H

#include "stack_structs.h"

unsigned long djb2(const char *str);

unsigned long hash_struct(my_stack *stk);

#endif