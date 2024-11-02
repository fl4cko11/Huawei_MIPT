#ifndef LIST_STRUCTS_H
#define LIST_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include<assert.h>

const int poisoned = 666;

typedef struct {
    int ind_next;
    int ind_prev;
    int next_free;
} neighbours_ind;

typedef struct {
    const char *name;
    const char *logname;
    size_t size;
    int *data;
    neighbours_ind *neighbours_indx;
    int FREE; // indx свободной
    int change_number;
} my_list;

#endif