#include "spu_calc.h"

size_t number_of_int_in_file(FILE *fp) {
    int temp = 0;
    size_t count = 0;
    while (fscanf(fp, "%d", &temp) == 1) {
        count++;
    }
    rewind(fp);
    return count;
}

void spu_code_buffer_ctor(char *pathname, my_SPU *spu, char *logname) {
    if (pathname == nullptr) {
        printf ("pathname err");
        exit(-1);
    }
    if (spu == nullptr) {
        printf ("spu err");
        exit(-1);
    }

    FILE *fp = fopen(pathname, "rb");
    if (!fp) {
        perror("No удалось открыть файл");
        exit(-1);
    }

    FILE *log_file = fopen(logname, "a");
    if (log_file == NULL) {
        perror("[stk] Error opening log file");
        return;
    }

    // Выделяем память для буфера
    spu->size_cb = number_of_int_in_file(fp);
    fprintf(log_file, "size code buffer: %ld\n", spu->size_cb);
    spu->code_buffer = (int *)calloc(spu->size_cb, sizeof(int));
    if (!spu->code_buffer) {
        perror("No удалось выделить память");
        fclose(fp);
        exit(-1);
    }

    //Заполняем буффер
    char cmd[50];
    int i = 0;
    while (fgets(cmd, sizeof(cmd), fp) != nullptr) {
        char *ptr_in_cmd = cmd;
        while (sscanf(ptr_in_cmd, "%d", &spu->code_buffer[i]) == 1) {
            i++;
            while (*ptr_in_cmd != '\0' && !isdigit(*ptr_in_cmd)) ptr_in_cmd++;  // пропускаем нечисловые символы
            while (isdigit(*ptr_in_cmd)) ptr_in_cmd++; // пропскаем считанное число
        }
    }
    
    fprintf(log_file, "code buffer: ");
    for (int i = 0; i < spu->size_cb; i++) {
        fprintf(log_file, "%d ", spu->code_buffer[i]);
    }
    fprintf(log_file, "\n");
    fprintf(log_file, "\n");

    fclose(fp);
    fclose(log_file);
}

void run(char *codefilename, char *logname) {
    my_stack stk ={};
    stack_ctor(&stk, logname);

    my_SPU spu = {};
    spu_code_buffer_ctor(codefilename, &spu, logname);

    bool if_run = true;
    int ip = 0;
    stackelem_t pop1 = 0;
    stackelem_t pop2 = 0;
    stackelem_t stke = 0;

    while (if_run) {
        switch (spu.code_buffer[ip]) {
            case push:
                stack_push(&stk, spu.code_buffer[ip+1]);
                ip += 2;
                break;
            case add:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_pop(&stk);
                pop2 = stk.popped;
                stack_push(&stk, pop1 + pop2);
                ip += 1;
                break;
            case sub:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_pop(&stk);
                pop2 = stk.popped;
                stack_push(&stk, pop2 - pop1);
                ip += 1;
                break;
            case my_div:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_pop(&stk);
                pop2 = stk.popped;
                stack_push(&stk, pop2/pop1);
                ip += 1;
                break;
            case mul:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_pop(&stk);
                pop2 = stk.popped;
                stack_push(&stk, pop2*pop1);
                ip += 1;
                break;
            case my_sqrt:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_push(&stk, sqrt(pop1));
                ip += 1;
                break;
            case my_sin:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_push(&stk, sin(pop1));
                ip += 1;
                break;
            case my_cos:
                stack_pop(&stk);
                pop1 = stk.popped;
                stack_push(&stk, cos(pop1));
                ip += 1;
                break;
            case out:
                printf("%d", stk.data[stk.size]);
                ip += 1;
                break;
            case in:
                printf("enter unit: ");
                scanf("%d", &stke);
                stack_push(&stk, stke);
                ip += 1;
                break;
            case dump:
                stack_dump(&stk);
                ip += 1;
                break;
            case hlt:
                stack_dtor(&stk);
                if_run = false;
                break;
        }
    }
}