#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct coefs {
    double a;
    double b;
    double c;
};

coefs quadro_input() {
    coefs coefs;
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

bool sign_of_diskr(double d) {
    return d > 0;
}

double diskr(double a, double b, double c) {
    return b * b - 4 * a * c;
}

void quadro_output(double a, double b, double c) {
    double root1, root2;
    bool hasRoot1 = false, hasRoot2 = false;

    if (a == 0) {
        if (b != 0) {
            root1 = -c / b;
            hasRoot1 = true;
        }
    } else {
        double d = diskr(a, b, c);
        if (sign_of_diskr(d)) {
            root1 = (-b + sqrt(d)) / (2 * a);
            root2 = (-b - sqrt(d)) / (2 * a);
            hasRoot1 = true;
            hasRoot2 = true;
        } else if (d == 0) {
            root1 = -b / (2 * a);
            hasRoot1 = true;
        }
    }
    
    if (hasRoot1) {
        printf("root1: %lf", root1);
        if (hasRoot2) {
            printf(", root2: %lf", root2);
        }
        printf("\n");
    } else {
        printf("no roots\n");
    }
}

int main() {
    coefs coefs = quadro_input();
    quadro_output(coefs.a, coefs.b, coefs.c);
    return 0;
}