#ifndef BST_STRUCTS_H
#define BST_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_t {
    int data;
    struct node_t *left;
    struct node_t *right;
} node_t;

typedef struct {
    node_t *root_node;
    //const char *logname;
    const char *name;
    int change_number;
} bst_t;

#endif