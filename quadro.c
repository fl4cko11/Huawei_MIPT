#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

struct coef
{
    double a;
    double b;
    double c;
};

struct roots
{
    double* root1;
    double* root2;
};

struct coef quadro_input() {
    struct coef coefs;
    coefs.a = 0;
    coefs.b = 0;
    coefs.c = 0;
    printf("Enter coefficient a: ");
    while (scanf("%lf", &coefs.a) != 1) {
        printf("Error input for a, try again: ");
        while (getchar() != '\n'); // очистка буфера ввода
    }

    printf("Enter coefficient b: ");
    while (scanf("%lf", &coefs.b) != 1) {
        printf("Error input for b, try again: ");
        while (getchar() != '\n'); // очистка буфера ввода
    }

    printf("Enter coefficient c: ");
    while (scanf("%lf", &coefs.c) != 1) {
        printf("Error input for c, try again: ");
        while (getchar() != '\n'); // очистка буфера ввода
    }

    return coefs;
}

bool sign_of_diskr(double d){
    if (d>0)
        return(true);
    else
        return(false);
}

double diskr(double a, double b, double c){
    return (b*b - 4*a*c);
}

struct roots quadro_output(double a, double b, double c) {
    struct roots roots;
    roots.root1 = NULL;
    roots.root2 = NULL;

    if (a == 0) {
        if (b != 0) {
            roots.root1 = (double*)malloc(sizeof(double));
            *roots.root1 = -c / b;
        }
        return roots;
    }

    double d = diskr(a, b, c);
    if (sign_of_diskr(d)) {
        roots.root1 = (double*)malloc(sizeof(double));
        roots.root2 = (double*)malloc(sizeof(double));
        *roots.root1 = (-b + sqrt(d)) / (2 * a);
        *roots.root2 = (-b - sqrt(d)) / (2 * a);
    } else if (d == 0) {
        roots.root1 = (double*)malloc(sizeof(double));
        *roots.root1 = -b / (2 * a);
    }

    return roots;
}

int main(){
    struct coef coefs = quadro_input();
    struct roots roots = quadro_output(coefs.a, coefs.b, coefs.c);
    if (roots.root2 == NULL)
    {
        printf("roots: %lf", *roots.root1);
        free(roots.root1);
        return 0;
    }
    else if (roots.root1 == NULL && roots.root2 == NULL)
    {
        printf("no roots");
        return 0;
    }
    else
    {
        printf("roots: %lf and %lf", *roots.root1, *roots.root2);       
        free(roots.root1);
        free(roots.root2);
        return 0;
    }
}