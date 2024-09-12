#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

struct coefs {
    double a;
    double b;
    double c;
};

struct roots{
    double root1;
    double root2;
    bool isroot1;
    bool isroot2;
};

double coef_input(char coef_name) {
    double coef;
    int result;
    while (1) { // бесконечный цикл, который завершится при корректном вводе
        printf("Enter coefficient %c: ", coef_name);
        result = scanf("%lf", &coef);
        
        if (result == 1) {
            break; // корректный ввод, выход из цикла
        } else {
            printf("Not correct input, try again!\n");
            while (getchar() != '\n'); // очистка буфера ввода
        }
    }
    return coef;
}


coefs quadro_input() {
    coefs coefs = {+INFINITY, +INFINITY, +INFINITY};
    coefs.a = coef_input('a');
    coefs.b = coef_input('b');
    coefs.c = coef_input('c');
    return coefs;
}

double diskr(double a, double b, double c) {
    return b * b - 4 * a * c;
}

roots quadro_solution(coefs coefs){
    roots roots = {+INFINITY, +INFINITY, false, false};

    if (coefs.a < DBL_MIN && coefs.a > -DBL_MIN) {
        if (coefs.b > DBL_MIN || coefs.b < -DBL_MIN) {
            roots.root1 = -coefs.c / coefs.b;
            roots.isroot1 = true;
        }
    } 
    else {
        double d = diskr(coefs.a, coefs.b, coefs.c);
        printf("diskr: %lf\n", d);
        if (d >= DBL_MIN) {
            roots.root1 = (-coefs.b + sqrt(d)) / (2 * coefs.a);
            roots.root2 = (-coefs.b - sqrt(d)) / (2 * coefs.a);
            roots.isroot1 = true;
            roots.isroot2 = true;
        } 
        else if (d < DBL_MIN && d>=0) {
            roots.root1 = -coefs.b / (2 * coefs.a);
            roots.isroot1 = true;
        }
        return roots;
    }
}

void quadro_output(roots roots) {
    if (roots.isroot1) {
        printf("root1: %lf", roots.root1);
        if (roots.isroot2) {
            printf(", root2: %lf", roots.root2);
        }
        printf("\n");
    } else {
        printf("no roots\n");
    }
}

int main() {
    quadro_output(quadro_solution(quadro_input()));
    return 0;
}