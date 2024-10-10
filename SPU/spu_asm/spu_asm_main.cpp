#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void command_cmp_and_writer(char cmd[], FILE *fp2) {
    char str_part_of_cmd[50];
    int temp = 0;
    if (sscanf(cmd, "%s %d", str_part_of_cmd, &temp) == 2) {
    if (strcmp("push", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 1);
    } 
    else if (strcmp("add", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 2);
    } 
    else if (strcmp("sub", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 3);
    } 
    else if (strcmp("div", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 4);
    } 
    else if (strcmp("mul", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 5);
    } 
    else if (strcmp("sqrt", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 6);
    } 
    else if (strcmp("sin", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 7);
    } 
    else if (strcmp("cos", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 8);
    } 
    else if (strcmp("out", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 9);
    } 
    else if (strcmp("in", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 10);
    } 
    else if (strcmp("dump", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 11);
    } 
    else if (strcmp("hlt", str_part_of_cmd) == 0) {
        fprintf(fp2, "%d ", 0);
    } 
    else {
        printf("SNTXERR\n");
        exit(-1);
    }

    fprintf(fp2, "%d\n", temp);
}

    else if (sscanf(cmd, "%s %d", str_part_of_cmd, &temp) == 1) {
        if (strcmp("push", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 1);
        } 
        else if (strcmp("add", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 2);
        } 
        else if (strcmp("sub", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 3);
        } 
        else if (strcmp("div", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 4);
        } 
        else if (strcmp("mul", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 5);
        } 
        else if (strcmp("sqrt", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 6);
        } 
        else if (strcmp("sin", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 7);
        } 
        else if (strcmp("cos", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 8);
        } 
        else if (strcmp("out", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 10);
        } 
        else if (strcmp("in", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 11);
        } 
        else if (strcmp("dump", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 12);
        } 
        else if (strcmp("hlt", str_part_of_cmd) == 0) {
            fprintf(fp2, "%d\n", 0);
        } 
        else {
            printf("SNTXERR\n");
            exit(-1);
        }
    }

    else {
        printf ("sscanf error");
        exit(-1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <full path to input_file> <full path to output_file>\n", argv[0]);
        return 1;
    }

    FILE *fp1 = fopen(argv[1], "rb");
    if (fp1 == nullptr) {
        perror("Error opening input file");
        return 1;
    }

    FILE *fp2 = fopen(argv[2], "w");
    if (fp2 == nullptr) {
        perror("Error opening output file");
        fclose(fp1);
        return 1;
    }

    char cmd[50];

    while (fgets(cmd, sizeof(cmd), fp1) != nullptr) {
        command_cmp_and_writer(cmd, fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}