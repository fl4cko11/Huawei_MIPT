#ifndef STACK_DOUBLE_VERIFY_H
#define STACK_DOUBLE_VERIFY_H

#include "stack_double_structs.h"
#include "stack_double_hash.h"

int is_poisoned(stackelem_t se);

void stack_dump(my_stack *stk);

void stack_error(my_stack *stk);

#endif