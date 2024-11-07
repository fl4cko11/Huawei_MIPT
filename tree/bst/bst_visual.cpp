#include "bst_structs.h"

void generate_dot(node_t *root, FILE *file) {
    if (root == NULL) {
        return;
    }

    // Добавляем рёбра для дочерних узлов
    if (root->left != NULL) {
        fprintf(file, "    %d -> %d [label=\"left\"];\n", root->data, root->left->data);
    }

    if (root->right != NULL) {
        fprintf(file, "    %d -> %d [label=\"right\"];\n", root->data, root->right->data);
    }

    // Рекурсивно вызываем для левого и правого поддеревьев
    generate_dot(root->left, file);
    generate_dot(root->right, file);
}

void generate_bst_dot_log_file(bst_t *bst, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Не удалось открыть файл для записи: %s\n", filename);
        return;
    }

    // Начало записи в DOT файл
    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");

    // Генерация DOT-строк для каждого узла
    if (&bst->nodes[0] != NULL) {
        generate_dot(&bst->nodes[0], file);
    }

    // Закрытие графа
    fprintf(file, "}\n");

    fclose(file);
}

void generate_bst_dot_log_image(bst_t *bst, int change_number) {
    char dot_filename[256];
    char img_filename[256];
    const char *dir = "bst_visual_log"; // Директория для сохранения

    // Формируем имена файлов с указанием пути
    snprintf(dot_filename, sizeof(dot_filename), "%s/bst_%d.dot", dir, change_number);
    snprintf(img_filename, sizeof(img_filename), "%s/bst_%d.png", dir, change_number);

    // Создаем директорию, если она не существует
    system("mkdir -p bst_visual_log");

    // Генерация DOT-файла
    generate_bst_dot_log_file(bst, dot_filename);

    // Генерация изображения с помощью Graphviz
    char command[512];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_filename, img_filename);
    system(command);
}