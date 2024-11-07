#include "bst_funcs.h"

int main() {
    bst_t bst_vasya = {};
    bst_ctor(&bst_vasya, "bst_vasya", 50);

    insert_value_in_bst(&bst_vasya, &bst_vasya.nodes[0], 30);
    insert_value_in_bst(&bst_vasya, &bst_vasya.nodes[0], 70);
    insert_value_in_bst(&bst_vasya, &bst_vasya.nodes[0], 10);
    insert_value_in_bst(&bst_vasya, &bst_vasya.nodes[0], 65);
    insert_value_in_bst(&bst_vasya, &bst_vasya.nodes[0], 80);

    return 0;
}