#include "spu_asm_funcs.h"

void lable_table_ctor(asm_lable_table *label_table, char *logname) {
    if (label_table == nullptr) {
        printf("[SPU] lable table ptr error\n");
        exit(-1);
    }
    if (logname == nullptr) {
        printf("[SPU] lable table ptr error\n");
        exit(-1);
    }

    label_table->label = (spu_label *)calloc(num_of_labels, sizeof(spu_label));
    if (label_table->label == nullptr) {
        printf("[SPU] calloc lable table err\n");
        exit(-1);
    }

    for (int i = 0; i < num_of_labels; i++) {
        label_table->label[i].ip = -1;
    }
    label_table->size = 0;
    label_table->logname = logname;
}

void lable_table_dump(asm_lable_table *label_table) {
    FILE *log_file = fopen(label_table->logname, "a");
    if (log_file == nullptr) {
        printf("[ASM] log_file open error\n");
        exit(-1);
    }

    fprintf(log_file, "[ASM] label table (names): ");
    for (int i = 0; i < num_of_labels; i++) {
        fprintf(log_file, "%s ", label_table->label[i].name);
    }
    fprintf(log_file, "\n");
    fprintf(log_file, "                  (ip for names): ");
    for (int i = 0; i < num_of_labels; i++) {
        fprintf(log_file, "%d ", label_table->label[i].ip);
    }
    fprintf(log_file, "\n");
    fprintf(log_file, "[ASM] lable table size: %lu\n\n", label_table->size);
    fclose(log_file);
}

int label_to_ip(char *arg_of_cmd, asm_lable_table *label_table) {
    for (int i = 0; i < num_of_labels; i++) {
        if (strcmp(arg_of_cmd, label_table->label[i].name) == 0) {
            return label_table->label[i].ip;
        }
    }
    return -1;
}

void print_to_asm_log (char *logname, char *cmd, char * command_part_of_cmd, char *arg_part_of_cmd, int ip_asm) {
    FILE *log_file = fopen(logname, "a");
    fprintf(log_file, "[ASM] ip_asm: %d\n", ip_asm);
    fprintf(log_file, "[ASM] cmd: %s\n", cmd);
    fprintf(log_file, "[ASM] command part of cmd: %s\n", command_part_of_cmd);
    fprintf(log_file, "[ASM] arg part of cmd: %s\n", arg_part_of_cmd);
    fprintf(log_file, "\n");
    fclose(log_file);
}

void ptr_in_cmd_to_arg(char *ptr_in_cmd, char *cmd) {
    int itterator = 0;
    while (cmd[itterator] != ' ') {
        itterator++;
        ptr_in_cmd++;
    }
    ptr_in_cmd++;
}

int command_cmp_and_writer(char cmd[], FILE *program_code, asm_lable_table *label_table, int ip_asm) {
    char *command_part_of_cmd = (char *)calloc(50, sizeof(char));
    char *arg_part_of_cmd = (char *)calloc(50, sizeof(char));
    sscanf(cmd, "%s %s", command_part_of_cmd, arg_part_of_cmd); //ПО ПРОБЕЛАМ ДЕЛИТ
    char *ptr_on_dbldot = strchr(command_part_of_cmd, ':'); // чек двоеточие для меток
    size_t str_len = 0;
    int temp = 0;
    int ip_label = 0;

    if (command_part_of_cmd != nullptr) {
        print_to_asm_log(label_table->logname, cmd, command_part_of_cmd, arg_part_of_cmd, ip_asm);

        if (strcmp("push", command_part_of_cmd) == 0) {
            if (arg_part_of_cmd[0] != '[') {

                if (sscanf(arg_part_of_cmd, "%d", &temp) == 1) { // push число
                    fprintf(program_code, "%d ", 1);
                    fprintf(program_code, "%d ", 1);
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 3;
                }

                else { // push из регистра
                    fprintf(program_code, "%d ", 1);
                    fprintf(program_code, "%d ", 2);
                    if (strcmp("ax", arg_part_of_cmd) == 0) {
                        fprintf(program_code, "%d\n", 0);
                        ip_asm += 3;
                    }
                    else if (strcmp("bx", arg_part_of_cmd) == 0) {
                        fprintf(program_code, "%d\n", 1);
                        ip_asm += 3;
                    }
                    else if (strcmp("cx", arg_part_of_cmd) == 0) {
                        fprintf(program_code, "%d\n", 2);
                        ip_asm += 3;
                    }
                    else if (strcmp("dx", arg_part_of_cmd) == 0) {
                        fprintf(program_code, "%d\n", 3);
                        ip_asm += 3;
                    }
                    else {
                        printf("[ASM] *no [* PUSH SYNTX ERROR\n");
                        exit(-1);
                    }
                }
            }
            else {
                fprintf(program_code, "%d ", 1);
                fprintf(program_code, "%d ", 7);

                char *ptr_on_plus_in_agr = strchr(arg_part_of_cmd, '+');
                //printf("[ASM] is correct start from +: %s\n", ptr_on_plus_in_agr);

                if (ptr_on_plus_in_agr != nullptr) { // если есть +
                    if (sscanf(arg_part_of_cmd, "[%d+%*s", &temp) == 1) { // игнорируем всё что за плюсом
                        //printf("int part of arg: %d\n", temp);
                        fprintf(program_code, "%d ", temp);

                        ptr_on_plus_in_agr++;
                        str_len = strlen(ptr_on_plus_in_agr);
                        ptr_on_plus_in_agr[str_len - 1] = '\0'; // убираем ]

                        //printf("is correct deleting of []: %s\n", ptr_on_plus_in_agr);

                        if (strcmp("ax", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 0);
                            ip_asm += 4;
                        }
                        else if (strcmp("bx", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 1);
                            ip_asm += 4;
                        }
                        else if (strcmp("cx", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 2);
                            ip_asm += 4;
                        }
                        else if (strcmp("dx", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 3);
                            ip_asm += 4;
                        }
                        else {
                        printf("[ASM] *[ and with +* POP SYNTX ERROR\n");
                        exit(-1);
                        }
                    }
                    else { // считаем, что нет [ax+ax], те у (+) всегда число должно быть
                        printf("[ASM] *ax+ax* POP SYNTX ERROR\n");
                        exit(-1);
                    }
                }
                else {
                    if (sscanf(arg_part_of_cmd, "[%d%*s", &temp) == 1) {
                        fprintf(program_code, "%d\n", temp);
                        ip_asm += 3;
                    }
                    else {
                        arg_part_of_cmd++; // уходим от [
                        str_len = strlen(arg_part_of_cmd);
                        arg_part_of_cmd[str_len - 1] = '\0'; // убираем ]
                        if (strcmp("ax", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 0);
                            ip_asm += 3;
                        }
                        else if (strcmp("bx", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 1);
                            ip_asm += 3;
                        }
                        else if (strcmp("cx", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 2);
                            ip_asm += 3;
                        }
                        else if (strcmp("dx", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 3);
                            ip_asm += 3;
                        }
                        else {
                            printf("[ASM] *[ and wo +* PUSH SYNTX ERROR\n");
                            exit(-1);
                        }
                    }
                }
            }
        }
        else if (strcmp("pop", command_part_of_cmd) == 0) {
            if (arg_part_of_cmd[0] == '\0') {
                fprintf(program_code, "%d ", 19);
                fprintf(program_code, "%d\n", 1);
                ip_asm += 2;
            }
            else if (arg_part_of_cmd[0] != '[') {
                fprintf(program_code, "%d ", 19);
                fprintf(program_code, "%d ", 2);
                if (strcmp("ax", arg_part_of_cmd) == 0) {
                    fprintf(program_code, "%d\n", 0);
                    ip_asm += 3;
                }
                else if (strcmp("bx", arg_part_of_cmd) == 0) {
                    fprintf(program_code, "%d\n", 1);
                    ip_asm += 3;
                }
                else if (strcmp("cx", arg_part_of_cmd) == 0) {
                    fprintf(program_code, "%d\n", 2);
                    ip_asm += 3;
                }
                else if (strcmp("dx", arg_part_of_cmd) == 0) {
                    fprintf(program_code, "%d\n", 3);
                    ip_asm += 3;
                }
                else {
                    printf("[ASM] *only reg* POP SYNTX ERROR\n");
                    exit(-1);
                }
            }
            else {
                fprintf(program_code, "%d ", 19);
                fprintf(program_code, "%d ", 7);
                
                char *ptr_on_plus_in_agr = strchr(arg_part_of_cmd, '+');

                if (ptr_on_plus_in_agr != nullptr) { // если есть +
                    if (sscanf(arg_part_of_cmd, "[%d+%*s", &temp) == 1) { // игнорируем всё что за плюсом
                        //printf("int part of arg: %d\n", temp);
                        fprintf(program_code, "%d ", temp);

                        ptr_on_plus_in_agr++;
                        str_len = strlen(ptr_on_plus_in_agr);
                        ptr_on_plus_in_agr[str_len - 1] = '\0'; // убираем ]

                        //printf("is correct deleting of []: %s\n", ptr_on_plus_in_agr);

                        if (strcmp("ax", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 0);
                            ip_asm += 4;
                        }
                        else if (strcmp("bx", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 1);
                            ip_asm += 4;
                        }
                        else if (strcmp("cx", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 2);
                            ip_asm += 4;
                        }
                        else if (strcmp("dx", ptr_on_plus_in_agr) == 0) {
                            fprintf(program_code, "%d\n", 3);
                            ip_asm += 4;
                        }
                        else {
                        printf("[ASM] *[ and with +* PUSH SYNTX ERROR\n");
                        exit(-1);
                        }
                    }
                    else { // считаем, что нет [ax+ax], те у (+) всегда число должно быть
                        printf("[ASM] *ax+ax* PUSH SYNTX ERROR\n");
                        exit(-1);
                    }
                }
                else {
                    if (sscanf(arg_part_of_cmd, "[%d%*s", &temp) == 1) {
                        fprintf(program_code, "%d\n", temp);
                        ip_asm += 3;
                    }
                    else {
                        arg_part_of_cmd++; // уходим от [
                        str_len = strlen(arg_part_of_cmd);
                        arg_part_of_cmd[str_len - 1] = '\0'; // убираем ]
                        if (strcmp("ax", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 0);
                            ip_asm += 3;
                        }
                        else if (strcmp("bx", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 1);
                            ip_asm += 3;
                        }
                        else if (strcmp("cx", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 2);
                            ip_asm += 3;
                        }
                        else if (strcmp("dx", arg_part_of_cmd) == 0) {
                            fprintf(program_code, "%d\n", 3);
                            ip_asm += 3;
                        }
                        else {
                            printf("[ASM] *[ and wo +* PUSH SYNTX ERROR\n");
                            exit(-1);
                        }
                    }
                }
            }
        }
        else if (strcmp("hlt", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 0);
            ip_asm++;
        }
        else if (strcmp("add", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 2);
            ip_asm++;
        } 
        else if (strcmp("sub", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 3);
            ip_asm++;
        } 
        else if (strcmp("div", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 4);
            ip_asm++;
        } 
        else if (strcmp("mul", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 5);
            ip_asm++;
        } 
        else if (strcmp("sqrt", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 6);
            ip_asm++;
        } 
        else if (strcmp("sin", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 7);
            ip_asm++;
        } 
        else if (strcmp("cos", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 8);
            ip_asm++;
        } 
        else if (strcmp("out", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 9);
            ip_asm++;
        } 
        else if (strcmp("in", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 10);
            ip_asm++;
        } 
        else if (strcmp("dump", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 11);
            ip_asm++;
        }
        else if (ptr_on_dbldot != nullptr) { // если есть метки
            if (label_table->size <= num_of_labels) {
                label_table->label[label_table->size].name = command_part_of_cmd;
                label_table->label[label_table->size].ip = ip_asm;
                label_table->size++;
                ip_asm++;
                lable_table_dump(label_table);
            }
            else {
                printf ("[ASM] too much labels\n");
                exit(-1);
            }
        }
        else if (strcmp("jump", command_part_of_cmd) == 0) {
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 12);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 12);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("ja", command_part_of_cmd) == 0) {
            ptr_in_cmd_to_arg(arg_part_of_cmd, cmd); // переводим к аргументу
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 13);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 13);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("jae", command_part_of_cmd) == 0) {
            ptr_in_cmd_to_arg(arg_part_of_cmd, cmd); // переводим к аргументу
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 14);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 14);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("jb", command_part_of_cmd) == 0) {
            ptr_in_cmd_to_arg(arg_part_of_cmd, cmd); // переводим к аргументу
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 15);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 15);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("jbe", command_part_of_cmd) == 0) {
            ptr_in_cmd_to_arg(arg_part_of_cmd, cmd); // переводим к аргументу
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 16);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 16);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("je", command_part_of_cmd) == 0) {
            ptr_in_cmd_to_arg(arg_part_of_cmd, cmd); // переводим к аргументу
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 17);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 17);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("jne", command_part_of_cmd) == 0) {
            ptr_in_cmd_to_arg(arg_part_of_cmd, cmd); // переводим к аргументу
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 18);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                fprintf(program_code, "%d ", 18);
                if (sscanf(arg_part_of_cmd, "%d", &temp) == 0) {
                    fprintf(program_code, "%d\n", temp);
                    ip_asm += 2;
                }
                else {
                    printf ("[ASM] SYNTAX ERR\n");
                    exit(-1);
                }
            }
        }
        else if (strcmp("call", command_part_of_cmd) == 0) {
            ptr_on_dbldot = strchr(arg_part_of_cmd, ':');
            if (ptr_on_dbldot != nullptr) { //если есть двоеточие у аргумента
                fprintf(program_code, "%d ", 20);
                ip_label = label_to_ip(arg_part_of_cmd, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);
                ip_asm += 2;
            }
            else {
                printf("[ASM] call syntax error...\n");
                exit(-1);
            }
        }
        else if (strcmp("return", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 21);
            ip_asm++;
        }
        else if (strcmp("start_", command_part_of_cmd) == 0) {
            fprintf(program_code, "%d\n", 22);
            ip_asm++;
        }
    }
    else {
        printf("[ASM] SYNTAX ERR NOT EXIST COMMAND\n");
        exit(-1);
    }

    return ip_asm;
}
