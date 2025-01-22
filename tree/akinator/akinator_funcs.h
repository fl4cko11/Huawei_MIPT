#ifndef AKINATOR_FUNCS_H
#define AKINATOR_FUNCS_H

#include "akinator_structs.h"
#include "akinator_visual.h"

static void generate_akr_dot_log(akr_t *akr);

node_t *create_node(const char *data);

char *prefix_buffer_from_akr_datafile(char *datafile_name, char *prefix_buffer);

static char *get_token(char **buf_ptr, char *token);

void akr_tree_from_prefix(char **buf_ptr, node_t **current_akr_root, akr_t *akr);

void akr_update_datafile(node_t *current_akr_root, FILE *datafile);

void akr_play(node_t *current_akr_root, akr_t *akr);

static int akr_get_def(node_t *current_akr_root, char *unit, way_buf_t **ptr_on_way_buffer);

void akr_get_def_interface(node_t *current_akr_root, char *unit);

#endif