#ifndef STACK_INT_STRUCTS_H
#define STACK_INT_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>

const long canary = 0xDEDA;
typedef int stackelem_t;
typedef int poisoned_stackelem_t;
const poisoned_stackelem_t poisoned_stackelem = 666;
const int reall_factor = 2;
const int reall_decreaser = 4; //less then reall_factor!!

typedef struct {
    long int hash_str;
    long int hash_data;
} stk_hash;

typedef struct {
    size_t canary_start;
    stackelem_t *data;
    size_t size;
    size_t capacity;
    stackelem_t popped;
    stk_hash hash;
    char *logname;
    size_t canary_end;
} my_stack;

#endif