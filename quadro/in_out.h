#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#include "quadro_structs.h"

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
            while (getchar() != '\n'); // очистка буфера ввода
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

void quadro_output(roots roots) {
    if (1 - isnan(roots.root1)) {
        printf("root1: %lf", roots.root1);
        if (1 - isnan(roots.root2)) {
            printf(", root2: %lf", roots.root2);
        }
        printf("\n");
    } 
    else {
        printf("no roots\n");
    }
}

#endif