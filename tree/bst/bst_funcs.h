#ifndef BST_FUNCS_H
#define BST_FUNCS_H

#include "bst_structs.h"
#include "bst_visual.h"

static void generate_bst_dot_log(bst_t *bst);

void bst_ctor(bst_t *bst, const char *name, int root_data);

void bst_postorder_dump(bst_t *bst, node_t *root_node_of_bst);

static void create_node_in_bst(bst_t *bst, int data);

int insert_value_in_bst(bst_t *bst, node_t *root_node_of_bst, int value);

#endif