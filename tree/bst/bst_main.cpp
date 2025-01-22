#include "bst_funcs.h"

int main() {
    bst_t bst_vasya = {};
    bst_ctor(&bst_vasya, "bst_vasya", 50);

    insert_value_in_bst(&bst_vasya, bst_vasya.root_node, 30);
    insert_value_in_bst(&bst_vasya, bst_vasya.root_node, 70);
    insert_value_in_bst(&bst_vasya, bst_vasya.root_node, 10);
    insert_value_in_bst(&bst_vasya, bst_vasya.root_node, 65);
    insert_value_in_bst(&bst_vasya, bst_vasya.root_node, 80);

    return 0;
}