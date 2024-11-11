#ifndef AKINATOR_VISUAL_H
#define AKINATOR_VISUAL_H

#include "akinator_funcs.h"

void generate_dot(node_t *root, FILE *file);

void generate_akr_dot_log_file(node_t *root, const char *filename);

void generate_akr_dot_log_image(node_t *root, int change_number);

#endif