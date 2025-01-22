#include "stack_int_funcs.h"
#include "stack_int_verify.h"

void stack_ctor(my_stack *stk, char *logname) {
    FILE *log_file = fopen(logname, "a"); // Открываем для записи, add to содержимое
    if (log_file == NULL) {
        printf("[STACK]  Error opening log file");
        exit(-1);
    }

    fprintf(log_file, "[STACK] start ctor\n");
    stk->logname = logname;
    stk->canary_start = canary;
    stk->canary_end = canary;
    stk->data = (stackelem_t *)calloc(2, sizeof(stackelem_t));
    stk->data[0] = canary;
    stk->size = 0;
    stk->capacity = reall_factor; // фактич капасити на 2 меньше (индексы 0 и капасити-1 для канареек)
    stk->data[stk->capacity - 1] = canary;
    stk->popped = poisoned_stackelem;
    djb2_stk(stk);
    fclose(log_file);

    stack_error(stk);
    stack_dump(stk);

    log_file = fopen(logname, "a");
    fprintf(log_file, "[STACK] end ctor!\n"); 
    fclose(log_file);
}

static void realloc_stack(my_stack *stk) {
    stack_error(stk);
    if (stk->size >= stk->capacity - 2) {
        stk->capacity = stk->capacity * reall_factor;
        stk->data = (stackelem_t *)realloc(stk->data, stk->capacity * sizeof(stackelem_t));
        if (stk->data == nullptr) {
            printf("[STACK] error stk in reall\n");
            exit(-1);
        }
        stk->data[stk->capacity - 1] = canary;
        for (int j = stk->size; j < stk->capacity - 1; j++) {
            stk->data[j] = poisoned_stackelem; // init 666 like poison and delete old canary
        }
        djb2_stk(stk);
        stack_error(stk);
    }
    else if (stk->size <= ((stk->capacity - 2) % reall_decreaser) && stk->capacity != 4) {
        stk->capacity = stk->capacity / reall_factor;
        stk->data = (stackelem_t *)realloc(stk->data, stk->capacity * sizeof(stackelem_t));
        if (stk->data == nullptr) {
            printf("[STACK] error stk in reall\n");
            exit(-1);
        }
        stk->data[stk->capacity - 1] = canary;
        djb2_stk(stk);
        stack_error(stk);
    }
}

void stack_push(my_stack *stk, stackelem_t elem) { // newest in end
    stack_error(stk);
    stk->size++;
    djb2_stk(stk);
    realloc_stack(stk); // stack_error inside
    stk->data[stk->size] = elem;
    djb2_stk(stk);
    stack_error(stk);
    stack_dump(stk);
}

void stack_pop(my_stack *stk) { // newest from end pop
    stack_error(stk);
    if (stk->data[stk->size] != canary) {
        stk->popped = stk->data[stk->size];
        stk->data[stk->size] = poisoned_stackelem;
        stk->size--;
        djb2_stk(stk);
        realloc_stack(stk); // stack_error inside
        stack_dump(stk);
    } else {
        FILE *log_file = fopen(stk->logname, "a");
        if (log_file == nullptr) {
            printf("[STACK] Error opening log file");
            exit(-1);
        }
        fprintf(log_file, "[STACK] nothing to pop...\n");
        fclose(log_file);
    }
}

void stack_dtor(my_stack *stk) {
    stack_error(stk);
    FILE *log_file = fopen(stk->logname, "a");
    if (log_file == nullptr) {
        printf("[STACK] Error opening log file");
        exit(-1);
    }
    fprintf(log_file, "[STACK] start dtor!\n");
    free(stk->data);
    stk->size = 0;
    stk->capacity = reall_factor;
    stk->popped = poisoned_stackelem;
    fprintf(log_file, "[STACK] end dtor\n");
    fclose(log_file);
}