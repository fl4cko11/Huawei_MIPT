#ifndef AKINATOR_FUNCS_H
#define AKINATOR_FUNCS_H

#include "akinator_structs.h"
#include "akinator_visual.h"

static void generate_akr_dot_log(akr_t *akr);

node_t *create_node(const char *data);

char *prefix_buffer_from_akr_datafile(char *datafile_name, char *prefix_buffer);

static char *get_token(char **buf_ptr, char *token);

void akr_tree_from_prefix(char **buf_ptr, node_t **current_akr_root, akr_t *akr);

void akr_prefix_dump(node_t *current_akr_root);

#endif