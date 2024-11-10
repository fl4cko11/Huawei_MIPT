#ifndef BST_VISUAL_H
#define BST_VISUAL_H

#include "bst_funcs.h"

void generate_dot(node_t *root, FILE *file);

void generate_bst_dot_log_file(node_t *root, const char *filename);

void generate_bst_dot_log_image(node_t *root, int change_number);

#endif