#include "stack_int_hash.h"

unsigned long djb2_struct(my_stack *stk) {
    unsigned long hash = 5381;
    long hash_adder = (long)stk->data;
    hash = ((hash << 5) + hash) + hash_adder;

    hash_adder = (long)stk->size;
    hash = ((hash << 5) + hash) + hash_adder;

    hash_adder = (long)stk->capacity;
    hash = ((hash << 5) + hash) + hash_adder;
    return hash;
}

unsigned long djb2_data(my_stack *stk) {
    unsigned long hash = 5381;
    long hash_adder = 0;
    for (int i = 1; i <= stk->size; i++) {
        hash = ((hash << 5) + hash) + stk->data[i];
    }
    return hash;
}

void djb2_stk(my_stack *stk) {
    stk->hash.hash_data = djb2_data(stk);
    stk->hash.hash_str = djb2_struct(stk);
}