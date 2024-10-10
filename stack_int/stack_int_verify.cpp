#include "stack_int_verify.h"

int is_poisoned(stackelem_t se) {
    return (se!=poisoned_stackelem);
}

void stack_dump(my_stack *stk) {
    FILE *log_file = fopen(stk->logname, "a");
    if (log_file == NULL) {
        perror("[stk] Error opening log file");
        return;
    }

    fprintf(log_file, "hash for struct: %ld\n", stk->hash.hash_str);
    fprintf(log_file, "hash for data: %ld\n", stk->hash.hash_data);
    fprintf(log_file, "adress of 1st elem of stk: %p\n", stk->data);
    fprintf(log_file, "size of stk: %lu\n", stk->size);
    fprintf(log_file, "capasity of stk (with canary in index: 0 and %lu): %lu\n", stk->capacity - 1, stk->capacity);

    fprintf(log_file, "stk wo canary: ");
    for (int i = 1; i < stk->size + 1; i++) {
        fprintf(log_file, "%d ", stk->data[i]);
    }
    fprintf(log_file, "\n");

    if (stk->data[stk->size + 1] != canary) {
        fprintf(log_file, "poisoned value (index in stk = %lu) %d\n", stk->size, stk->data[stk->size + 1]);
    }

    if (stk->capacity - 2 != 0 && is_poisoned(stk->data[stk->capacity - 2])) {
        fprintf(log_file, "another poisoned value (index in stk = %lu) %d\n", stk->capacity - 2 - 1, stk->data[stk->capacity - 2]);
    }

    if (is_poisoned(stk->popped)) {
        fprintf(log_file, "popped elem: %d\n", stk->popped);
    }

    fprintf(log_file, "\n");
    fclose(log_file);
}

void stack_error(my_stack *stk) {
    FILE *log_file = fopen(stk->logname, "a");
    if (log_file == NULL) {
        perror("[stk] Error opening log file");
        return;
    }

    int is_fatal = 0;
    if (stk == nullptr) {
        fprintf(log_file, "stk ptr error, exit...\n");
        fclose(log_file);
        exit(-1);
    }

    if (stk->canary_start != canary) {
        fprintf(log_file, "Left Canary of struct changed!\n");
        is_fatal = 1;
    }

    if (stk->canary_end != canary) {
        fprintf(log_file, "Right Canary of struct changed!\n");
        is_fatal = 1;
    }

    if (stk->data == nullptr) {
        fprintf(log_file, "data ptr is null!\n");
        is_fatal = 1;
    }

    if (stk->data[0] != canary) {
        fprintf(log_file, "Left Canary of data changed!\n");
        is_fatal = 1;
    }

    if (stk->data[stk->capacity - 1] != canary) {
        fprintf(log_file, "Right Canary of data changed!\n");
        is_fatal = 1;
    }

    if (stk->hash.hash_str != djb2_struct(stk)) {
        fprintf(log_file, "HASH struct changed!\n");
        is_fatal = 1;
    }

    if (stk->hash.hash_data != djb2_data(stk)) {
        fprintf(log_file, "HASH data changed!\n");
        is_fatal = 1;
    }

    if (stk->size > stk->capacity + 1) {
        fprintf(log_file, "size more cap!?\n");
        is_fatal = 1;
    }

    if (stk->size < 0) {
        fprintf(log_file, "size value error\n");
        is_fatal = 1;
    }

    if (stk->capacity < 0) {
        fprintf(log_file, "cap value error\n");
        is_fatal = 1;
    }

    if (is_fatal == 1) {
        fclose(log_file);
        exit(-1);
    }

    fclose(log_file);
}