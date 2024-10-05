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
typedef double poisoned_stackelem_t;
const poisoned_stackelem_t poisoned_stackelem = NAN;
const int reall_factor = 2;
const int reall_decreaser = 4; //less then reall_factor!!

typedef enum {
    ALL_GOOD = 0,
    LEFT_CANARY_OF_STR_CH = -1,
    RIGHT_CANARY_OF_STR_CH = -2,
    LEFT_CANARY_OF_DATA_CH = -3,
    RIGHT_CANARY_OF_DATA_CH = -4,
    HASH_CH = -5,
    DATA_PTR_NULL = -6,
    SIZE_MORE_CAP = -7,
    SIZE_VALUE_ERROR = -8,
    CAP_VALUE_ERROR = -9
} errors_codes;

typedef struct {
    long int hash_str;
    long int hash_data;
} stk_hash;

typedef struct {
    uint32_t canary_start;
    stackelem_t *data;
    size_t size;
    size_t capacity;
    stackelem_t popped;
    stk_hash hash;
    uint32_t canary_end;
} my_stack;

#endif