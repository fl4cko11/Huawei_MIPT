#include "stack_funcs.h"

int main(){
    my_stack stk = {};
    stack_ctor(&stk);
    stack_push(&stk, 10);
    stack_push(&stk, 11);
    stack_push(&stk, 12);
    stack_push(&stk, 3);
    stack_pop(&stk);
    stack_dtor(&stk);
    return 0;
}