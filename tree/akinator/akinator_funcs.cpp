#include "akinator_funcs.h"

static void generate_akr_dot_log(akr_t *akr) {
    assert(akr != nullptr);
    if (akr->change_number != 0) {
        generate_akr_dot_log_image(akr->root_node, akr->change_number);
    }
    akr->change_number++;
}

node_t *create_node(const char *data) {
    assert(data != nullptr);

    node_t *new_node = (node_t*)calloc(1, sizeof(node_t));
    assert(new_node != nullptr);

    new_node->data = strdup(data);
    new_node->yes = nullptr;
    new_node->no = nullptr;

    return new_node;
}

char *prefix_buffer_from_akr_datafile(char *datafile_name, char *prefix_buffer) {
    assert(datafile_name != nullptr);
    assert(prefix_buffer != nullptr);

    FILE *datafile = fopen(datafile_name, "rb");
    assert(datafile != nullptr);

    fgets(prefix_buffer, buffers_size, datafile);
    fprintf(stderr, "[akr_funcs] pref buf: %s\n", prefix_buffer);

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

    while (**buf_ptr != '"') {
        token[itter] = **buf_ptr;
        itter++;
        *buf_ptr = *buf_ptr + 1;
    }
    token[itter] = '\0';
    *buf_ptr = *buf_ptr + 1; // сдвигаем с кавычки

    return token;
}

void akr_tree_from_prefix(char **buf_ptr, node_t **current_akr_root, akr_t *akr) { //всего акинатора для логов
    assert(buf_ptr != nullptr);
    assert(current_akr_root != nullptr);
    assert(akr != nullptr);
    
    //fprintf(stderr, "[akr] курсор: %c\n", **buf_ptr);
    if (**buf_ptr == '{') {
        *buf_ptr = *buf_ptr + 1; // на токен в кавычках

        char token[256];
        token[0] = '\0';
        get_token(buf_ptr, token);
        fprintf(stderr, "[akr_funcs] token: %s\n", token);

        node_t *new_node = create_node(token);
        *current_akr_root = new_node;
        generate_akr_dot_log(akr);

        if (**buf_ptr == '}') {
            *buf_ptr = *buf_ptr + 1;
            return;
        }
        akr_tree_from_prefix(buf_ptr, &((*current_akr_root)->yes), akr); // рекурсивно строим левое дерево (в префиксной записи считаем, что сначала левое указывается)
        akr_tree_from_prefix(buf_ptr, &((*current_akr_root)->no), akr); // рекурсивно строим правое дерево
        *buf_ptr = *buf_ptr + 1; // конец подкоренного дерева 
    }
    return;
}

void akr_update_datafile(node_t *current_akr_root, FILE *datafile) {
    assert(datafile != nullptr);
    assert(current_akr_root != nullptr);

    if (!current_akr_root) {
        fprintf(stderr, "void node, file aint updated\n");
        return;
    }
    fprintf(datafile, "{");
    fprintf(datafile, "\"%s\"", current_akr_root->data);
    if(current_akr_root->yes) akr_update_datafile(current_akr_root->yes, datafile);
    if(current_akr_root->no) akr_update_datafile(current_akr_root->no, datafile);
    fprintf(datafile, "}");
}

static void play_akr(node_t *current_akr_root, akr_t *akr) { //всего акинатора для логов
    assert(current_akr_root != nullptr);
    assert(akr != nullptr);

    char answ = '\0';
    char long_answ[answ_buffers_size];
    fprintf(stdout, "[akr play] Have your object such signs: %s\n", current_akr_root->data);
    fprintf(stdout, "[akr play] Y/N: ");
    scanf(" %c", &answ);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // для корреткного ввода удаляем \n из stdin (чисто специфика fgets)

    if (answ == 'Y') {
        if (current_akr_root->yes->yes != nullptr) play_akr(current_akr_root->yes, akr); // если есть уточняющий вопрос
        else {
            fprintf(stdout, "[akr play] EZ, this is: %s\n", current_akr_root->yes->data);
            fprintf(stdout, "[akr play] THATS RIGHT??? Y/N: ");
            scanf(" %c", &answ);
            while ((ch = getchar()) != '\n' && ch != EOF);

            if (answ == 'Y') {
                fprintf(stdout, "[akr play] BYE BYE...\n");
                return;
            }
        
            else {
                fprintf(stdout, "[akr play] Looks like I don't know this item, let's add it in\n");
                fprintf(stdout, "[akr play] Formulate a question that would distinguish yours from the previous one: ");
                fgets(long_answ, answ_buffers_size, stdin);
                long_answ[strcspn(long_answ, "\n")] = '\0';  // Убираем символ новой строки
                char *tmp = current_akr_root->yes->data;
                current_akr_root->yes->data = strdup(long_answ);
                fprintf(stdout, "[akr play] Who that was?: ");
                fgets(long_answ, answ_buffers_size, stdin);
                long_answ[strcspn(long_answ, "\n")] = '\0';  // Убираем символ новой строки
                node_t *new_Y_node = create_node(strdup(long_answ));
                node_t *new_N_node = create_node(tmp);
                current_akr_root->yes->yes = new_Y_node;
                current_akr_root->yes->no = new_N_node;
                fprintf(stdout, "[akr play] Successfully added bye bye...\n");
                generate_akr_dot_log(akr);
                return;
            }
        }
    }
    else if (current_akr_root->no != nullptr) {
        if (current_akr_root->no->yes != nullptr) play_akr(current_akr_root->no, akr); // если уточняющий вопрос есть
        else {
            fprintf(stdout, "[akr play] EZ, this is: %s\n", current_akr_root->no->data);
            fprintf(stdout, "[akr play] THATS RIGHT??? Y/N: ");
            scanf(" %c", &answ);
            while ((ch = getchar()) != '\n' && ch != EOF);

            if (answ == 'Y') {
                fprintf(stdout, "[akr play] BYE BYE...\n");
                return;
            }

            else {
                fprintf(stdout, "[akr play] Looks like I don't know this item, let's add it in\n");
                fprintf(stdout, "[akr play] Formulate a question that would distinguish yours from the previous one: ");
                fgets(long_answ, answ_buffers_size, stdin);
                long_answ[strcspn(long_answ, "\n")] = '\0';  // Убираем символ новой строки
                char *tmp = current_akr_root->no->data;
                current_akr_root->no->data = strdup(long_answ);
                fprintf(stdout, "[akr play] Who that was?: ");
                fgets(long_answ, answ_buffers_size, stdin);
                long_answ[strcspn(long_answ, "\n")] = '\0';  // Убираем символ новой строки
                node_t *new_Y_node = create_node(strdup(long_answ));
                node_t *new_N_node = create_node(tmp);
                current_akr_root->no->yes = new_Y_node;
                current_akr_root->no->no = new_N_node;
                fprintf(stdout, "[akr play] Successfully added bye bye...\n");
                generate_akr_dot_log(akr);
                return;
            }
        }
    }
    return;
}

void play_akr_interface(node_t *current_akr_root, akr_t *akr) { //всего акинатора для логов
    assert(current_akr_root != nullptr);
    assert(akr != nullptr);

    char answ;
    fprintf(stdout, "[akr intrf] Hello, wanna play? Y/N: ");
    scanf(" %c", &answ);
    if (answ == 'Y') {
        play_akr(current_akr_root, akr);
    }
    else {
        fprintf(stdout, "[akr intrf] OK, cancel...\n");
        return;
    }
    return;
}