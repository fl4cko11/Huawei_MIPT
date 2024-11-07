#ifndef BST_VISUAL_H
#define BST_VISUAL_H

#include "bst_funcs.h"

void generate_dot(node_t *root, FILE *file);

void generate_bst_dot_log_file(bst_t *bst, const char *filename);

void generate_bst_dot_log_image(bst_t *bst, int change_number);

#endif