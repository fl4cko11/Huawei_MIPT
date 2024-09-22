#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#include "quadro_structs.h"

// declaration - объявление
// definition - определение

double diskr(double a, double b, double c);

double diskr(double a, double b, double c) { // definition
    return b * b - 4 * a * c;
}

roots quadro_solution(coefs coefs){
    roots roots = {NAN, NAN};
    if (coefs.a == 0) {
        if (coefs.b != 0) {
            roots.root1 = -coefs.c / coefs.b;
        }
    } 
    else {
        double d = diskr(coefs.a, coefs.b, coefs.c);
        if (d >= 0) {
            double sqr_d = sqrt(d); //из-за точности дабла может в 0 уйти
            if (sqr_d != 0){
                roots.root1 = (-coefs.b + sqrt(d)) / (2 * coefs.a);
                roots.root2 = (-coefs.b - sqrt(d)) / (2 * coefs.a);
            } 
            else {
                roots.root1 = -coefs.b / (2 * coefs.a);
            }
        }
    }
    return roots;
}

#endif