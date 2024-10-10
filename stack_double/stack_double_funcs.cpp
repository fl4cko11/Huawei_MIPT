#include "stack_double_funcs.h"
#include "stack_double_verify.h"

void stack_ctor(my_stack *stk, char *logname) {
    FILE *log_file = fopen(logname, "w"); // Открываем для записи, очищая содержимое
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    fprintf(log_file, "start ctor\n");
    stk->canary_start = canary;
    stk->canary_end = canary;
    stk->data = (stackelem_t *)calloc(2, sizeof(stackelem_t));
    stk->data[0] = canary;
    stk->size = 0;
    stk->capacity = reall_factor; // фактич капасити на 2 меньше (индексы 0 и капасити-1 для канареек)
    stk->data[stk->capacity - 1] = canary;
    stk->popped = poisoned_stackelem;
    djb2_stk(stk);
    fprintf(log_file, "end ctor!\n");
    stack_error(stk, logname);
    stack_dump(stk, logname); 

    fclose(log_file);
}

static void realloc_stack(my_stack *stk, char *logname) {
    FILE *log_file = fopen(logname, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    fprintf(log_file, "start realloc stk...\n");
    stack_error(stk, logname);
    if (stk->size >= stk->capacity - 2) {
        fprintf(log_file, "start incr cap...\n");
        stk->capacity = stk->capacity * reall_factor;
        stk->data = (stackelem_t *)realloc(stk->data, stk->capacity * sizeof(stackelem_t));
        if (stk->data == nullptr) {
            fprintf(log_file, "data ptr error! exit...\n");
            fclose(log_file);
            exit(-1);
        }
        stk->data[stk->capacity - 1] = canary;
        for (int j = stk->size; j < stk->capacity - 1; j++) {
            stk->data[j] = poisoned_stackelem; // init NAN like poison and delete old canary
        }
        djb2_stk(stk);
        stack_error(stk, logname);
        fprintf(log_file, "end realloc incr\n");
    }
    else if (stk->size <= ((stk->capacity - 2) % reall_decreaser) && stk->capacity != 4) {
        fprintf(log_file, "start decr cap...\n");
        stk->capacity = stk->capacity / reall_factor;
        stk->data = (stackelem_t *)realloc(stk->data, stk->capacity * sizeof(stackelem_t));
        if (stk->data == nullptr) {
            fprintf(log_file, "data ptr error! exit...\n");
            fclose(log_file);
            exit(-1);
        }
        stk->data[stk->capacity - 1] = canary;
        djb2_stk(stk);
        stack_error(stk, logname);
        fprintf(log_file, "end realloc decr\n");
    }

    fclose(log_file);
}

void stack_push(my_stack *stk, stackelem_t elem, char *logname) { // newest in end
    FILE *log_file = fopen(logname, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    fprintf(log_file, "start pushing...\n");
    stack_error(stk, logname);
    stk->size++;
    djb2_stk(stk);
    realloc_stack(stk, logname); // stack_error inside
    stk->data[stk->size] = elem;
    djb2_stk(stk);
    stack_error(stk, logname);
    fprintf(log_file, "end pushing!\n");
    stack_dump(stk, logname);

    fclose(log_file);
}

void stack_pop(my_stack *stk, char *logname) { // newest from end pop
    FILE *log_file = fopen(logname, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    fprintf(log_file, "started popping\n");
    stack_error(stk, logname);
    if (stk->data[stk->size] != canary) {
        stk->popped = stk->data[stk->size];
        stk->data[stk->size] = poisoned_stackelem;
        stk->size--;
        djb2_stk(stk);
        realloc_stack(stk, logname); // stack_error inside
        fprintf(log_file, "end pop!\n");
        stack_dump(stk, logname);
    } else {
        fprintf(log_file, "nothing to pop...\n");
    }

    fclose(log_file);
}

void stack_dtor(my_stack *stk, char *logname) {
    FILE *log_file = fopen(logname, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    fprintf(log_file, "start dtor!\n");
    stack_error(stk, logname);
    free(stk->data);
    stk->size = 1;
    stk->capacity = reall_factor;
    stk->popped = poisoned_stackelem;
    fprintf(log_file, "end dtor\n");

    fclose(log_file);
}