#include "stack_hash.h"

unsigned long djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash;
}

unsigned long hash_struct(my_stack *stk) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%p%d%d", stk->data, stk->size, stk->capacity);
    return djb2(buffer);
}