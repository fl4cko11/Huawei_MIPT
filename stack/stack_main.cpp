#include "stack_funcs.h"

int main(){
    my_stack stk = {};
    stack_ctor(&stk);
    stack_push(&stk, 10);
    stack_push(&stk, 12);
    stack_push(&stk, 13);
    stack_push(&stk, 14);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_dtor(&stk); //popped elem in stk->popped
    return 0;
}