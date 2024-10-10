#include "stack_double_funcs.h"

int main(int argc, char *argv[]){
    my_stack stk = {};
    stack_ctor(&stk, argv[1]);
    stack_push(&stk, 10, argv[1]);
    stack_pop(&stk, argv[1]);
    stack_pop(&stk, argv[1]);
    stack_pop(&stk, argv[1]);
    stack_pop(&stk, argv[1]);
    stack_pop(&stk, argv[1]);
    stack_dtor(&stk, argv[1]); //popped elem in stk->popped
    return 0;
}