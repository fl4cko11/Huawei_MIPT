#include "bst_funcs.h"

static void generate_bst_dot_log(bst_t *bst) {
    generate_bst_dot_log_image(bst, bst->change_number);
    bst->change_number++;
}

void bst_ctor(bst_t *bst, const char *name, int root_data) {
    assert(bst != nullptr);
    assert(name != nullptr);

    bst->nodes = (node_t *)calloc(bst_max_size, sizeof(node_t));
    bst->size = 0;
    bst->nodes[0].data = root_data;
    bst->nodes[0].left = nullptr;
    bst->nodes[0].right = nullptr;
    bst->name = name;
    bst->change_number = 0;
}

void bst_postorder_dump(bst_t *bst, node_t *root_node_of_bst) {
    fprintf(stderr, "(");
    fprintf(stderr, "%d", root_node_of_bst->data);
    if (root_node_of_bst->left) bst_postorder_dump(bst, root_node_of_bst->left);
    if (root_node_of_bst->right) bst_postorder_dump(bst, root_node_of_bst->right);
    fprintf(stderr, ")");
}

static void create_node_in_bst(bst_t *bst, int data) {
    assert(bst != nullptr);

    bst->nodes[bst->size].data = data;
    bst->nodes[bst->size].left = nullptr;
    bst->nodes[bst->size].right = nullptr;
}

int insert_value_in_bst(bst_t *bst, node_t *root_node_of_bst, int value) {
    assert(bst != nullptr);
    assert(root_node_of_bst != nullptr);

    if (root_node_of_bst->data > value) {
        if (root_node_of_bst->left != nullptr) insert_value_in_bst(bst, root_node_of_bst->left, value);
        else {
            bst->size++;
            if (bst->size >= bst_max_size) {
                fprintf(stderr, "too much nodes, cant insert value\n");
                return -1;
            }
            create_node_in_bst(bst, value);
            root_node_of_bst->left = &bst->nodes[bst->size];
            generate_bst_dot_log(bst);
            return 0;
        }
    }

    else if (root_node_of_bst->data < value) {
        if (root_node_of_bst->right != nullptr) insert_value_in_bst(bst, root_node_of_bst->right, value);
        else {
            bst->size++;
            if (bst->size >= bst_max_size) {
                fprintf(stderr, "too much nodes, cant insert value\n");
                return -1;
            }
            create_node_in_bst(bst, value);
            root_node_of_bst->right = &bst->nodes[bst->size];
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
