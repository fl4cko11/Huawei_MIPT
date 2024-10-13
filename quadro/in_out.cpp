#include "in_out.h"

void buffer_clean() {
    while (getchar() != '\n');
}

double coef_input(char coef_name) {
    double coef = NAN; // init
    int result = 0;
    while (1) { // бесконечный цикл, который завершится при корректном вводе
        printf("Enter coefficient %c: ", coef_name);
        result = scanf("%lf", &coef);
        if (result == 1) {
            break; // корректный ввод, выход из цикла
        } 
        else {
            printf("Not correct input, try again!\n");
            buffer_clean();
        }
    }
    return coef;
}

coefs quadro_input() {
    coefs coefs = {NAN, NAN, NAN}; // NAN
    coefs.a = coef_input('a');
    coefs.b = coef_input('b');
    coefs.c = coef_input('c');
    return coefs;
}

void quadro_output(roots *roots) {
    if (!isnan(roots->root1)) { // !isnan
        printf("root1: %lf", roots->root1);
        if (!isnan(roots->root2)) {
            printf(", root2: %lf", roots->root2);
        }
        printf("\n");
    }
    else {
        printf("no roots\n");
    }
}