#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>

typedef enum {
    hlt = 0,
    push = 1,
    add = 2,
    sub = 3,
    div = 4,
    mul = 5,
    sqrt = 6,
    sin = 7,
    cos = 8,
    out = 9,
    in = 10,
    dump = 11
} my_machine_code;


#endif