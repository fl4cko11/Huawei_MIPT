#include "stack_verify.h"

int is_poisoned(stackelem_t se) {
    return (!isnan(se));
}

void stack_dump(my_stack *stk) {
    printf("hash for struct: %ld\n", stk->hash.hash_str);
    printf("hash for data: %ld\n", stk->hash.hash_data);
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
    if (stk->capacity == 2) {}
    else printf("another poisoned value (index in stk = %d) %f\n", stk->capacity - 2 - 1, stk->data[stk->capacity - 2]);
    if (is_poisoned(stk->popped)){
        printf("popped elem: %f\n", stk->popped);
    }
    printf("\n");
    printf("\n");
}

void stack_error(my_stack *stk) {
    int is_fatal = 0;
    assert(stk!=nullptr);

    if (stk->canary_start != CANARY_VALUE) {
        printf("Left Canary of struct changed!\n");
        is_fatal = 1;
    }

    if (stk->canary_end != CANARY_VALUE) {
        printf("Right Canary of struct changed!\n");
        is_fatal = 1;
    }

    if (stk->data == nullptr) {
        printf("data ptr is null!\n");
        is_fatal = 1;
    }

    if (stk->data[0] != CANARY_VALUE) {
        printf("Left Canary of data changed!\n");
        is_fatal = 1;
    }

    if (stk->data[stk->capacity - 1] != CANARY_VALUE) {
        printf("Right Canary of data changed!\n");
        is_fatal = 1;
    }

    if (stk->hash.hash_str != djb2_struct(stk)) {
        printf("HASH struct changed!\n");
        is_fatal = 1;
    }

    if (stk->hash.hash_data != djb2_data(stk)) {
        printf("HASH data changed!\n");
        is_fatal = 1;
    }

    if (stk->size > stk->capacity) {
        printf("size more cap!?\n");
        is_fatal = 1;
    }

    if (stk->size < 1) {
        printf("size value erroe\n");
        is_fatal = 1;
    }

    if (stk->capacity < 0) {
        printf("cap value error\n");
        is_fatal = 1;
    }

    if (is_fatal == 1) {
        exit(-1);
    }

    else {
        printf("ALL GOOD...\n");
        printf("\n");
    }
}