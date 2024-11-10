#include "bst_funcs.h"

static void generate_bst_dot_log(bst_t *bst) {
    generate_bst_dot_log_image(bst->root_node, bst->change_number);
    bst->change_number++;
}

void bst_ctor(bst_t *bst, const char *name, int root_data) {
    assert(bst != nullptr);
    assert(name != nullptr);

    bst->root_node = (node_t *)calloc(1, sizeof(node_t));
    bst->root_node->data = root_data;
    bst->root_node->left = nullptr;
    bst->root_node->right = nullptr;
    bst->name = name;
    bst->change_number = 0;
}

node_t *create_node(int data) {
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

    new_node->data = data;
    new_node->left = nullptr;
    new_node->right = nullptr;
    return new_node;
}

int insert_value_in_bst(bst_t *bst, node_t *current_root_node_of_bst, int value) { // всё дерево передаю только для логов (в релизе можно без)
    assert(bst != nullptr);
    assert(current_root_node_of_bst != nullptr);

    if (current_root_node_of_bst->data > value) {
        if (current_root_node_of_bst->left != nullptr) insert_value_in_bst(bst, current_root_node_of_bst->left, value);
        else {
            node_t *new_node = create_node(value);
            current_root_node_of_bst->left = new_node;
            generate_bst_dot_log(bst);
            return 0;
        }
    }

    else if (current_root_node_of_bst->data < value) {
        if (current_root_node_of_bst->right != nullptr) insert_value_in_bst(bst, current_root_node_of_bst->right, value);
        else {
            node_t *new_node = create_node(value);
            current_root_node_of_bst->right = new_node;
            generate_bst_dot_log(bst);
            return 0;
        }
    }

    else {
        fprintf(stderr, "already exist such node\n");
        return 0;
    }

    return -1;
}
