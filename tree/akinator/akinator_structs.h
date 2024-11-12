#ifndef AKINATOR_STRUCTS_H
#define AKINATOR_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

const size_t buffers_size = 1024;
const size_t answ_buffers_size = 256;

typedef struct node_t {
    char *data;
    struct node_t *yes;
    struct node_t *no;
} node_t;

typedef struct {
    node_t *root_node;
    int change_number;
} akr_t;

typedef struct {
    char *data;
    int yes_or_no;
} way_buf_t;

#endif