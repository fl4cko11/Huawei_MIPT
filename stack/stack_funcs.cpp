#include "stack_funcs.h"
#include "stack_verify.h"

void stack_ctor(my_stack *stk) {
    printf("start ctor\n");
    stk->canary_start = CANARY_VALUE;
    stk->canary_end = CANARY_VALUE;
    stk->data = (stackelem_t *)calloc(2, sizeof(stackelem_t));
    stk->data[0] = CANARY_VALUE;
    stk->size = 1; // 1 = 0
    stk->capacity = reall_factor;
    stk->data[stk->capacity - 1] = CANARY_VALUE;
    stk->popped = poisoned_stackelem;
    stk->hash.hash_str = djb2_struct(stk);
    stk->hash.hash_data = djb2_data(stk);
    printf("end ctor!\n");
    stack_error(stk);
    stack_dump(stk); 
}

void realloc_incr_stack(my_stack *stk) {
    printf("start realloc incr\n");
    stack_error(stk);
    stk->capacity = stk->capacity*reall_factor;
    stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
    assert(stk->data != nullptr);
    stk->data[stk->capacity - 1] = CANARY_VALUE;
    for (int j = stk->size + 1; j < stk->capacity - 1; j++) {
        stk->data[j] = poisoned_stackelem; //init NAN like posion and delete old canary
    }
    stk->hash.hash_str = djb2_struct(stk);
    stk->hash.hash_data = djb2_data(stk);
    printf("end realloc incr\n");
    stack_error(stk);
    printf("\n");
}

void realloc_decr_stack(my_stack *stk) {
    printf("start reall decr\n");
    stack_error(stk);
    stk->capacity = stk->capacity/reall_factor;
    stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
    assert(stk->data != nullptr);
    stk->data[stk->capacity - 1] = CANARY_VALUE;
    stk->hash.hash_str = djb2_struct(stk);
    stk->hash.hash_data = djb2_data(stk);
    printf("end realloc decr!\n");
    stack_error(stk);
    printf("\n");
}

void stack_push(my_stack *stk, stackelem_t elem) { //newest in end
    printf("start pushing...\n");
    stack_error(stk);
    if (stk->size < stk->capacity - 1) { //in the last elem in data - canary => -1
        stk->data[stk->size] = elem;
        stk->size++;
        stk->hash.hash_str = djb2_struct(stk);
        stk->hash.hash_data = djb2_data(stk);
        printf("end pushing!\n");
        stack_error(stk);
        stack_dump(stk);
    }
    else {
        realloc_incr_stack(stk);
        stk->data[stk->size] = elem;
        stk->size++;
        stk->hash.hash_str = djb2_struct(stk);
        stk->hash.hash_data = djb2_data(stk);
        printf("end pushing!\n");
        stack_error(stk);
        stack_dump(stk);
    }
}

void stack_pop(my_stack *stk) { //newest from end pop
    printf("started popping\n");
    stack_error(stk);
    if (stk->size - 1 > (stk->capacity%reall_decreaser)) {
        stk->popped = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = poisoned_stackelem;
        stk->size--;
        stk->hash.hash_str = djb2_struct(stk);
        stk->hash.hash_data = djb2_data(stk);
        printf("end pop!\n");
        stack_error(stk);
        stack_dump(stk);
    }
    else {
        realloc_decr_stack(stk); //mem economy
        stk->popped = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = poisoned_stackelem;
        stk->size--;
        stk->hash.hash_str = djb2_struct(stk);
        stk->hash.hash_data = djb2_data(stk);
        printf("end pop!\n");
        stack_error(stk);
        stack_dump(stk);
    }
}

void stack_dtor(my_stack *stk) {
    printf("start dtor!\n");
    stack_error(stk);
    free(stk->data);
    stk->size = 1;
    stk->capacity = reall_factor;
    stk->popped = poisoned_stackelem;
    printf("end dtor\n");
}