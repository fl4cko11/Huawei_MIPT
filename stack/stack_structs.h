#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>

#define CANARY_VALUE 0xDEDA
typedef double stackelem_t;
const int reall_factor = 2;
const int reall_decreaser = 4; //less then reall_factor!!

typedef struct {
    uint32_t canary_start;
    stackelem_t *data;
    int size;
    int capacity;
    stackelem_t popped;
    long int hash;
    uint32_t canary_end;
} my_stack;

#endif