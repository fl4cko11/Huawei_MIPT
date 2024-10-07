#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include "stack_structs.h"
#include "stack_hash.h"
#include "stack_verify.h"

void stack_ctor(my_stack *stk);

void realloc_stack(my_stack *stk);

void stack_push(my_stack *stk, stackelem_t elem);

void stack_pop(my_stack *stk);

void stack_dtor(my_stack *stk);

#endif