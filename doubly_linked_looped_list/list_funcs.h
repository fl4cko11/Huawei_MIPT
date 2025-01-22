#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H
#include "list_structs.h"

static void list_verify(my_list *list);

static void list_dump_and_verify(my_list *list);

void list_ctor(my_list *list, const char *name, const char *logname, size_t size);

int *get_front_ptr(my_list *list);

int get_front_indx(my_list *list);

int *get_back_ptr(my_list *list);

int get_back_indx(my_list *list);

int get_user_anchor_unit_index_in_data(my_list *list, int user_index_anchor_unit);

void push_front(my_list *list, int insert_unit);

void push_back(my_list *list, int insert_unit);

void push_front_of_unit(my_list *list, int insert_unit, int index_anchor_unit);

void push_back_of_unit(my_list *list, int insert_unit, int index_anchor_unit);

void delete_unit(my_list *list, int index_delete_unit);

void list_dtor(my_list *list);

#endif