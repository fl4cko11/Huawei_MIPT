#ifndef QUADRO_STRUCTS_H
#define QUADRO_STRUCTS_H

typedef struct {
    double root1;
    double root2;
} roots;

typedef struct{
    double a;
    double b;
    double c;
} coefs;

typedef struct{
    roots exp_roots;
    roots res_roots;
} quadro_tests;

#endif