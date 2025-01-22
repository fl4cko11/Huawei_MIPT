#include "spu_asm_funcs.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <full path to asm_file> <full path to code_file> <name or full path of asm_log_file>\n", argv[0]);
        return 1;
    }

    FILE *prorgam_asm = fopen(argv[1], "rb");
    if (prorgam_asm == nullptr) {
        printf("[SPU_ASM] Error opening input file");
        fclose(prorgam_asm);
        exit(-1);
    }
    FILE *program_code = fopen(argv[2], "w");
    if (program_code == nullptr) {
        perror("[SPU_ASM] Error opening output file");
        fclose(program_code);
        exit(-1);
    }

    FILE *for_cleanup_log = fopen(argv[3], "w");
    fclose (for_cleanup_log);

    asm_lable_table label_table = {};
    lable_table_ctor(&label_table, argv[3]);
    lable_table_dump(&label_table);

    int ip_asm = 0; // for ip of label

    char *cmd = (char *)calloc(50, sizeof(char));
    if (cmd == nullptr) {
        printf("[SPU_ASM] cmd error\n");
        exit(-1);
    }

    while (fgets(cmd, 50, prorgam_asm) != nullptr) {
        size_t len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n') {
            cmd[len - 1] = '\0';
        }
        ip_asm = command_cmp_and_writer(cmd, program_code, &label_table, ip_asm);
    }

    fclose(prorgam_asm);
    fclose(program_code);
    return 0;
}