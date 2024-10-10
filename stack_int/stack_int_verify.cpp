#include "stack_int_verify.h"

int is_poisoned(stackelem_t se) {
    return (se!=poisoned_stackelem);
}

void stack_dump(my_stack *stk) {
    printf("hash for struct: %ld\n", stk->hash.hash_str);
    printf("hash for data: %ld\n", stk->hash.hash_data);
    printf("adress of 1st elem of stk: %p\n", stk->data);
    printf("size of stk: %lu\n", stk->size);
    printf("capasity of stk (with canary in index: 0 and %lu): %lu\n", stk->capacity -1, stk->capacity);

    printf("stk wo canary: ");
    for (int i = 1; i < stk->size + 1; i++) {
        printf("%d ", stk->data[i]);
    }
    printf("\n");

    if (stk->data[stk->size + 1] != canary) {
        printf("poisoned value (index in stk = %lu) %d\n", stk->size, stk->data[stk->size + 1]);
    }

    if (stk->capacity - 2 != 0 && is_poisoned(stk->data[stk->capacity - 2])) {
        printf("another poisoned value (index in stk = %lu) %d\n", stk->capacity - 2 - 1, stk->data[stk->capacity - 2]);
    }

    if (is_poisoned(stk->popped)){
        printf("popped elem: %d\n", stk->popped);
    }

    printf("\n");
    printf("\n");
}

void stack_error(my_stack *stk) {
    int is_fatal = 0;
    if (stk == nullptr) {
        printf("stk ptr error, exit...");
        exit(-1);
    }

    if (stk->canary_start != canary) {
        printf("Left Canary of struct changed!\n");
        is_fatal = 1;
    }

    if (stk->canary_end != canary) {
        printf("Right Canary of struct changed!\n");
        is_fatal = 1;
    }

    if (stk->data == nullptr) {
        printf("data ptr is null!\n");
        is_fatal = 1;
    }

    if (stk->data[0] != canary) {
        printf("Left Canary of data changed!\n");
        is_fatal = 1;
    }

    if (stk->data[stk->capacity - 1] != canary) {
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

    if (stk->size > stk->capacity + 1) {
        printf("size more cap!?\n");
        is_fatal = 1;
    }

    if (stk->size < 0) {
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
}