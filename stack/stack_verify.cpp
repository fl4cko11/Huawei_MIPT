#include "stack_verify.h"

void stack_dump(my_stack *stk) {
    printf("adress of 1st elem of stk: %p\n", stk->data);
    printf("size of stk: %d\n", stk->size - 1);
    printf("capasity of stk: %d\n", stk->capacity);
    printf("stk wo canary: ");
    for (int i = 1; i < stk->size; i++) {
        if (stk->data[i] != CANARY_VALUE) {
            printf("%f ", stk->data[i]);
        }
    }
    printf("\n");
    printf("poisoned value (index in stk = %d) %f\n", stk->size - 1, stk->data[stk->size]);
    printf("another poisoned value (index in stk = %d) %f\n", stk->capacity - 2 - 1, stk->data[stk->capacity - 2]);
    if (!isnan(stk->popped)){
        printf("popped elem: %f\n", stk->popped);
    }
    printf("hash for struct: %ld\n", stk->hash);
    printf("\n");
    printf("\n");
}

int stack_error(my_stack *stk) {
    if (stk->canary_start != CANARY_VALUE || stk->canary_end != CANARY_VALUE) {
        printf ("Canary of struct changed!");
        return -1;
    }

    if (stk->hash != hash_struct(stk)) {
        printf ("HASH changed!");
        return -1;
    }

    if (stk->data[0] != CANARY_VALUE || stk->data[stk->capacity - 1] != CANARY_VALUE) {
        printf ("Canary of data changed!");
        return -1;
    }

    assert(stk != nullptr);
    assert(stk->data != nullptr);
    assert(stk->size < stk->capacity);

    if (stk->size < 1) {
        printf("stk size error");
        return -1;
    }
    if (stk->capacity < 0) {
        printf("stk capacity error");
        return -1;
    }

    return 0;
}