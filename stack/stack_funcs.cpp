#include "stack_funcs.h"

void stack_ctor(my_stack *stk) {
    stk->canary_start = CANARY_VALUE;
    stk->canary_end = CANARY_VALUE;
    stk->data = (stackelem_t *)calloc(2, sizeof(stackelem_t));
    stk->data[0] = CANARY_VALUE;
    stk->size = 1; // 1 = 0
    stk->capacity = reall_factor;
    stk->data[stk->capacity - 1] = CANARY_VALUE;
    stk->popped = NAN;
    stk->hash = hash_struct(stk);
    printf("ctor!\n");
    stack_dump(stk); 
}

my_stack *realloc_incr_stack(my_stack *stk) {
    stk->capacity = stk->capacity*reall_factor;
    stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
    stk->data[stk->capacity - 1] = CANARY_VALUE;
    for (int j = stk->size + 1; j < stk->capacity - 1; j++) {
        stk->data[j] = NAN; //init NAN like posion and delete old canary
    }
    return stk;
}

my_stack *realloc_decr_stack(my_stack *stk) {
    stk->capacity = stk->capacity/reall_factor;
    stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
    stk->data[stk->capacity - 1] = CANARY_VALUE;
    return stk;
}

void stack_push(my_stack *stk, stackelem_t elem) { //newest in end
    if (stack_error(stk) == 0) {
        if (stk->size < stk->capacity - 1) {
            stk->data[stk->size] = elem;
            stk->size++;
            stk->hash = hash_struct(stk);
        }
        else {
            stk = realloc_incr_stack(stk);
            stk->data[stk->size] = elem;
            stk->size++;
            stk->hash = hash_struct(stk);
        }
    printf("push!\n");
    stack_dump(stk);
    }
}

void stack_pop(my_stack *stk) { //newest from end pop
    if (stack_error(stk) == 0) {
        if (stk->size - 1 > (stk->capacity%reall_decreaser)) {
            stk->popped = stk->data[stk->size - 1];
            stk->data[stk->size - 1] = NAN;
            stk->size--;
            stk->hash = hash_struct(stk);
        }
        else {
            stk = realloc_decr_stack(stk); //mem economy
            stk->popped = stk->data[stk->size - 1];
            stk->data[stk->size - 1] = NAN;
            stk->size--;
            stk->hash = hash_struct(stk);
        }
    printf("pop!\n");
    stack_dump(stk);
    }
}

void stack_dtor(my_stack *stk) {
    printf("dtor!\n");
    free(stk->data);
    stk->size = 1;
    stk->capacity = reall_factor;
    stk->popped = NAN;
}