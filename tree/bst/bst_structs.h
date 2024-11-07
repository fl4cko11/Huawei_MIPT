#ifndef BST_STRUCTS_H
#define BST_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const size_t bst_max_size = 10;

typedef struct node_t {
    int data;
    struct node_t *left;
    struct node_t *right;
} node_t;

typedef struct {
    node_t *nodes;
    size_t size;
    //const char *logname;
    const char *name;
    int change_number;
} bst_t;

#endif