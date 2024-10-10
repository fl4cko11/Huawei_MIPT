#ifndef STACK_DOUBLE_FUNCS_H
#define STACK_DOUBLE_FUNCS_H

#include "stack_double_structs.h"
#include "stack_double_hash.h"
#include "stack_double_verify.h"

void stack_ctor(my_stack *stk, char *logname);

static void realloc_stack(my_stack *stk);

void stack_push(my_stack *stk, stackelem_t elem);

void stack_pop(my_stack *stk);

void stack_dtor(my_stack *stk);

#endif