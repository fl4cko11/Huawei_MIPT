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

int first_spec_symb_in_str(char *str) {
    int ind = 0;
    while (isalpha(str[ind]) || str[ind] == ' ') {
        ind++;
    }
    return ind;
}

int label_to_ip(char *temp_s, asm_lable_table *label_table) {
    for (int i = 0; i < num_of_labels; i++) {
        if (strcmp(temp_s, label_table->label[i].name) == 0) {
            return label_table->label[i].ip;
        }
    }
    return -1;
}

int command_cmp_and_writer(char cmd[], FILE *program_code, asm_lable_table *label_table, int ip_asm) {
    char *str_part_of_cmd = (char *)calloc(50, sizeof(char));
    int temp = 0;
    char *temp_s = (char *)calloc(20, sizeof(char));

    FILE *log_file = fopen(label_table->logname, "a");

    if (sscanf(cmd, "%s %d", str_part_of_cmd, &temp) == 2) { //команды с численным аргументом
        if (strcmp("push", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 1);
            ip_asm += 2;
        }
        else if (strcmp("jump", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 12);
            ip_asm += 2;
        }
        else if (strcmp("ja", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 13);
            ip_asm += 2;
        }
        else if (strcmp("jae", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 14);
            ip_asm += 2;
        }
        else if (strcmp("jb", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 15);
            ip_asm += 2;
        }
        else if (strcmp("jbe", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 16);
            ip_asm += 2;
        }
        else if (strcmp("je", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 17);
            ip_asm += 2;
        }
        else if (strcmp("jne", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 18);
            ip_asm += 2;
        }
        else {
            printf("SNTXERR\n");
            exit(-1);
        }

        fprintf(program_code, "%d\n", temp);
    }

    else if (sscanf(cmd, "%s %s", str_part_of_cmd, temp_s) == 2) { //команды с строковым аргументом
        int ind_of_1st_spec = first_spec_symb_in_str(temp_s);
        int ip_label = 0;
        bool if_reg = false; //safety for jump ax not work
        bool if_label = false;

        if (strcmp("pushr", str_part_of_cmd) == 0) { // число из регистра в стк
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 19);
            ip_asm += 2;
            if_reg = true;
        }
        else if (strcmp("popr", str_part_of_cmd) == 0) { // число из стека в регистр
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 20);
            ip_asm += 2;
            if_reg = true;
        }
        else if (strcmp("jump", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 12);
            ip_asm += 2;
            if_label = true;
        }
        else if (strcmp("ja", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 13);
            ip_asm += 2;
            if_label = true;
        }
        else if (strcmp("jae", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 14);
            ip_asm += 2;
            if_label = true;
        }
        else if (strcmp("jb", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 15);
            ip_asm += 2;
            if_label = true;
        }
        else if (strcmp("jbe", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 16);
            ip_asm += 2;
            if_label = true;
        }
        else if (strcmp("je", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 17);
            ip_asm += 2;
            if_label = true;
        }
        else if (strcmp("jne", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d ", 18);
            ip_asm += 2;
            if_label = true;
        }
        else {
            printf("SNTXERR\n");
            exit(-1);
        }

        if (if_reg) {
            if (strcmp("ax", temp_s) == 0) {
                fprintf(program_code, "%d\n", 0);
            }
            else if (strcmp("bx", temp_s) == 0) {
                fprintf(program_code, "%d\n", 1);
            }
            else if (strcmp("cx", temp_s) == 0) {
                fprintf(program_code, "%d\n", 2);
            }
            else if (strcmp("dx", temp_s) == 0) {
                fprintf(program_code, "%d\n", 3);
            }
        }
        else if (if_label) {
            if (temp_s[ind_of_1st_spec] = ':') {
                ip_label = label_to_ip(temp_s, label_table);
                if (ip_label == -1) {
                    printf("[ASM] not existing label...\n");
                    exit(-1);
                }
                fprintf(program_code, "%d\n", ip_label);  
            }
        }
        else {
            printf("SNTXERR\n");
            exit(-1);
        }
    }

    else if (sscanf(cmd, "%s", str_part_of_cmd) == 1) { //одиночные команды и метки
        int ind_of_1st_spec = first_spec_symb_in_str(cmd);

        if (strcmp("hlt", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 0);
            ip_asm++;
        } 
        else if (strcmp("add", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 2);
            ip_asm++;
        } 
        else if (strcmp("sub", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 3);
            ip_asm++;
        } 
        else if (strcmp("div", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 4);
            ip_asm++;
        } 
        else if (strcmp("mul", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 5);
            ip_asm++;
        } 
        else if (strcmp("sqrt", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 6);
            ip_asm++;
        } 
        else if (strcmp("sin", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 7);
            ip_asm++;
        } 
        else if (strcmp("cos", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 8);
            ip_asm++;
        } 
        else if (strcmp("out", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 9);
            ip_asm++;
        } 
        else if (strcmp("in", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 10);
            ip_asm++;
        } 
        else if (strcmp("dump", str_part_of_cmd) == 0) {
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fprintf(program_code, "%d\n", 11);
            ip_asm++;
        }
        else if (str_part_of_cmd[ind_of_1st_spec] == ':') { // считка меток
            fprintf(log_file, "[ASM] stroka: %d\n", ip_asm);
            fprintf(log_file, "[ASM] cmd: %s\n", cmd);
            fclose(log_file);
            if (label_table->size <= num_of_labels) {
                label_table->label[label_table->size].name = str_part_of_cmd;
                label_table->label[label_table->size].ip = ip_asm;
                label_table->size++;
                ip_asm++;
                lable_table_dump(label_table);
                log_file = fopen(label_table->logname, "a"); // because 2 free
            }
            else {
                printf ("[ASM] too much labels\n");
                exit(-1);
            }
        }
        else {
            printf("SNTXERR\n");
            exit(-1);
        }
    }

    else {
        printf ("sscanf error\n");
        exit(-1);
    }
    
    fclose(log_file);

    return ip_asm;
}
