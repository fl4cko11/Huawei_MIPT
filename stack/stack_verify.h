#ifndef STACK_VERIFY_H
#define STACK_VERIFY_H

#include "stack_structs.h"
#include "stack_hash.h"

void stack_dump(my_stack *stk);

int stack_error(my_stack *stk);

#endif