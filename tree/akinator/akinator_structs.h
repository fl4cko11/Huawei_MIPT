#ifndef AKINATOR_STRUCTS_H
#define AKINATOR_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const size_t buffers_size = 1000;
const size_t answ_buffers_size = 100;

typedef struct node_t {
    char *data;
    struct node_t *yes;
    struct node_t *no;
} node_t;

typedef struct {
    node_t *root_node;
    int change_number;
} akr_t;

#endif