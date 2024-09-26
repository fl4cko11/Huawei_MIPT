#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef double stackelem_t;
const int reall_factor = 2;
const int reall_decrease = 4; //less then reall_factor!!

struct my_stack {
    stackelem_t *data;
    int size;
    int capacity;
    stackelem_t popped;
};

void stack_ctor(my_stack *stk) {
    stk->data = (stackelem_t *)malloc(1*sizeof(stackelem_t));
    stk->data[0] = NAN;
    stk->size = 1;
    stk->capacity = reall_factor;
    stk->popped = NAN; 
}

my_stack *realloc_inc_stack(my_stack *stk){
    stk->capacity = stk->capacity*reall_factor;
    stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
    for (int j = stk->size; j < stk->capacity; j++) {
        stk->data[j] = NAN; //init NAN for safety
    }
    return stk;
}

my_stack *realloc_dec_stack(my_stack *stk){
    stk->capacity = stk->capacity/reall_factor;
    stk->data = (stackelem_t *)realloc(stk->data, stk->capacity*sizeof(stackelem_t));
    return stk;
}

void stack_push(my_stack *stk, stackelem_t elem) { //newest in end
    if (stk->size < stk->capacity) {
        stk->data[stk->size] = elem;
        stk->size++;
    }

    else {
        stk = realloc_inc_stack(stk);
        stk->data[stk->size] = elem;
        stk->size++;
    }
}

void stack_pop(my_stack *stk) { //newest from end pop
    if (stk->size > 0 && stk->size - 1 > (stk->capacity%reall_decrease)) {
        stk->popped = stk->data[stk->size-1];
        stk->data[stk->size-1] = NAN;
        stk->size--;
    }

    else if (stk->size > 0) {
        stk = realloc_dec_stack(stk);
        stk->popped = stk->data[stk->size-1];
        stk->data[stk->size-1] = NAN;
        stk->size--;
    }

    else if (stk->size <= 0) {
        printf("nothing to pop, bruh\n");
    }
}

void stack_dtor(my_stack *stk) {
    free(stk->data);
    stk->data[0] = NAN;
    stk->size = 1;
    stk->capacity = reall_factor;
    stk->popped = NAN;
}

int main(){
    my_stack stk = {};
    stack_ctor(&stk);
    printf("stk ctor: check size: %d\n", stk.size);
    printf("stk ctor: check cap: %d\n", stk.capacity);
    printf("\n");

    stack_push(&stk, 10);
    printf("stk after push: check size: %d\n", stk.size);
    printf("stk after push: check cap: %d\n", stk.capacity);
    printf("stk after push: check last elem: %f\n", stk.data[stk.size-1]);
    printf("\n");

    stack_push(&stk, 3.2);
    printf("stk after push: check size: %d\n", stk.size);
    printf("stk after push: check cap: %d\n", stk.capacity);
    printf("stk after push: check last elem: %f\n", stk.data[stk.size-1]);
    printf("\n");

    stack_pop(&stk);
    printf("stk after pop: check size: %d\n", stk.size);
    printf("stk after pop: check cap: %d\n", stk.capacity);
    printf("stk after pop: check last elem: %f\n", stk.data[stk.size-1]);
    printf("stk after pop: check popped: %f\n", stk.popped);
    printf("\n");

    stack_pop(&stk);
    printf("stk after pop: check size: %d\n", stk.size);
    printf("stk after pop: check cap: %d\n", stk.capacity);
    printf("stk after pop: check last elem: %f\n", stk.data[stk.size-1]);
    printf("stk after pop: check popped: %f\n", stk.popped);
    printf("\n");

    stack_pop(&stk);
    printf("stk after pop: check size: %d\n", stk.size);
    printf("stk after pop: check cap: %d\n", stk.capacity);
    printf("stk after pop: check last elem: %f\n", stk.data[stk.size-1]);
    printf("stk after pop: check popped: %f\n", stk.popped);
    printf("\n");

    stack_pop(&stk);
    printf("stk after pop: check size: %d\n", stk.size);
    printf("stk after pop: check cap: %d\n", stk.capacity);
    printf("stk after pop: check last elem: %f\n", stk.data[stk.size-1]);
    printf("stk after pop: check popped: %f\n", stk.popped);
    printf("\n");

    stack_push(&stk, 1.1);
    printf("stk after push: check size: %d\n", stk.size);
    printf("stk after push: check cap: %d\n", stk.capacity);
    printf("stk after push: check last elem: %f\n", stk.data[stk.size-1]);
    printf("\n");

    return 0;
}