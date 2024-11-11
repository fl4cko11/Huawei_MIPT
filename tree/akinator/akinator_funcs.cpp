#include "akinator_funcs.h"

static void generate_akr_dot_log(akr_t *akr) {
    assert(akr != nullptr);
    if (akr->change_number != 0) {
        generate_akr_dot_log_image(akr->root_node, akr->change_number);
    }
    akr->change_number++;
}

node_t *create_node(const char *data) {
    node_t *new_node = (node_t*)calloc(1, sizeof(node_t));
    assert(new_node != nullptr);

    new_node->data = strdup(data);
    new_node->yes = nullptr;
    new_node->no = nullptr;

    return new_node;
}

char *prefix_buffer_from_akr_datafile(char *datafile_name, char *prefix_buffer) {
    FILE *datafile = fopen(datafile_name, "rb");
    assert(datafile != nullptr);

    fgets(prefix_buffer, buffers_size, datafile);
    fprintf(stderr, "[akr] pref buf: %s\n", prefix_buffer);

    fclose(datafile);
    return prefix_buffer;
}

static char *get_token(char **buf_ptr, char *token) {
    assert(buf_ptr != nullptr);
    assert(*buf_ptr != nullptr);
    assert(token != nullptr);

    int itter = 0;
    if (**buf_ptr == '"') {
        *buf_ptr = *buf_ptr + 1;
    }

    //fprintf(stderr, "[akr in token before while] %c\n", **buf_ptr);
    while (**buf_ptr != '"') {
        token[itter] = **buf_ptr;
        itter++;
        *buf_ptr = *buf_ptr + 1;
        //fprintf(stderr, "%c", **buf_ptr);
    }
    //fprintf(stderr, "\n");
    *buf_ptr = *buf_ptr + 1; // сдвигаем с кавычки
    //fprintf(stderr, "[akr in token after while] %c\n", **buf_ptr);

    return token;
}

void akr_tree_from_prefix(char **buf_ptr, node_t **current_akr_root, akr_t *akr) { //всего акинатора для логов
    fprintf(stderr, "[akr] курсор: %c\n", **buf_ptr);
    if (**buf_ptr == '{') {
        *buf_ptr = *buf_ptr + 1; // на токен в кавычках

        char token[256];
        token[0] = '\0';
        get_token(buf_ptr, token);
        fprintf(stderr, "[akr] token: %s\n", token);

        node_t *new_node = create_node(token);
        *current_akr_root = new_node;
        generate_akr_dot_log(akr);

        akr_tree_from_prefix(buf_ptr, &((*current_akr_root)->yes), akr); // рекурсивно строим левое дерево (в префиксной записи считаем, что сначала левое указывается)
        akr_tree_from_prefix(buf_ptr, &((*current_akr_root)->no), akr); // рекурсивно строим правое дерево
    }
    else if (**buf_ptr == '}') {
        *buf_ptr = *buf_ptr + 1; // сдвигаемся с } и ливаем с рекурсии
        return;
    }
    return;
}

void akr_prefix_dump(node_t *current_akr_root) {
    if (!current_akr_root) {
        fprintf(stderr, "void node\n");
        return;
    }
    fprintf(stderr, "{");
    fprintf(stderr, "%s", current_akr_root->data);
    if(current_akr_root->yes) akr_prefix_dump(current_akr_root->yes);
    if(current_akr_root->no) akr_prefix_dump(current_akr_root->no);
    fprintf(stderr, "}");
}