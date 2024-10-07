#include "stack_funcs.h"
#include "stack_verify.h"

void stack_ctor(my_stack *stk) {
    printf("start ctor\n");
    stk->canary_start = canary;
    stk->canary_end = canary;
    stk->data = (stackelem_t *)calloc(2, sizeof(stackelem_t));
    stk->data[0] = canary;
    stk->size = 0;
    stk->capacity = reall_factor; // фактич капасити на 2 меньше (индексы 0 и капасити-1 для канареек)
    stk->data[stk->capacity - 1] = canary;
    stk->popped = poisoned_stackelem;
    djb2_stk(stk);
    printf("end ctor!\n");
    stack_error(stk);
    stack_dump(stk); 
}

void realloc_stack(my_stack *stk) {
    printf("start realloc stk...\n");
    stack_error(stk);
    if (stk->size >= stk->capacity - 2) {
        printf("start incr cap...\n");
        stk->capacity = stk->capacity*reall_factor;
        stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
        if (stk->data == nullptr) {
            printf ("data ptr error! exit...\n");
            exit(-1);
        }
        stk->data[stk->capacity - 1] = canary;
        for (int j = stk->size; j < stk->capacity - 1; j++) {
            stk->data[j] = poisoned_stackelem; //init NAN like posion and delete old canary
        }
        djb2_stk(stk);
        stack_error(stk);
        printf("end realloc incr\n");
    }

    else if (stk->size <= ((stk->capacity - 2)%reall_decreaser) && stk->capacity != 4) {
        printf("start decr cap...\n");
        stk->capacity = stk->capacity/reall_factor;
        stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
        if (stk->data == nullptr) {
            printf ("data ptr error! exit...\n");
            exit(-1);
        }
        stk->data[stk->capacity - 1] = canary;
        djb2_stk(stk);
        stack_error(stk);
        printf("end realloc decr\n");
    }
}

void stack_push(my_stack *stk, stackelem_t elem) { //newest in end
    printf("start pushing...\n");
    stack_error(stk);
    stk->size++;
    djb2_stk(stk);
    realloc_stack(stk); //stack_error inside
    stk->data[stk->size] = elem;
    djb2_stk(stk);
    stack_error(stk);
    printf("end pushing!\n");
    stack_dump(stk);
}

void stack_pop(my_stack *stk) { //newest from end pop
    printf("started popping\n");
    stack_error(stk);
    if (stk->data[stk->size] != canary) {
        stk->popped = stk->data[stk->size];
        stk->data[stk->size] = poisoned_stackelem;
        stk->size--;
        djb2_stk(stk);
        realloc_stack(stk); //stack_error inside
        printf("end pop!\n");
        stack_dump(stk);
    }
    else printf("nothing to pop...\n");
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