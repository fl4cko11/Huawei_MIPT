#include "stack_double_funcs.h"

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Usage: %s <full path to log_stk_file>\n", argv[0]);
        return 1;
    }
    my_stack stk = {};
    stack_ctor(&stk, argv[1]);
    stack_push(&stk, 10);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_dtor(&stk); //popped elem in stk->popped
    return 0;
}