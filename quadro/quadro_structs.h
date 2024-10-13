#ifndef QUADRO_STRUCTS_H
#define QUADRO_STRUCTS_H

typedef struct {
    double root1;
    double root2;
} roots;

typedef struct {
    double a;
    double b;
    double c;
} coefs;

typedef struct {
    coefs test_coefs;
    roots exp_roots;
    const char *testname;
} quadro_tests;

#endif