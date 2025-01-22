#include "akinator_structs.h"

void generate_dot(node_t *root, FILE *file) {
    if (root == NULL) {
        return;
    }

    // Добавляем рёбра для дочерних узлов
    if (root->yes != NULL) {
    fprintf(file, "    \"%s\" -> \"%s\" [label=\"yes\"];\n", root->data, root->yes->data);
    }

    if (root->no != NULL) {
        fprintf(file, "    \"%s\" -> \"%s\" [label=\"no\"];\n", root->data, root->no->data);
    }

    // Рекурсивно вызываем для левого и правого поддеревьев
    generate_dot(root->yes, file);
    generate_dot(root->no, file);
}

void generate_akr_dot_log_file(node_t *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Не удалось открыть файл для записи: %s\n", filename);
        return;
    }

    // Начало записи в DOT файл
    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");

    // Генерация DOT-строк для каждого узла
    if (root != NULL) {
        generate_dot(root, file);
    }

    // Закрытие графа
    fprintf(file, "}\n");

    fclose(file);
}

void generate_akr_dot_log_image(node_t *root, int change_number) {
    char dot_filename[256];
    char img_filename[256];
    const char *dir = "bst_visual_log"; // Директория для сохранения

    // Формируем имена файлов с указанием пути
    snprintf(dot_filename, sizeof(dot_filename), "%s/bst_%d.dot", dir, change_number);
    snprintf(img_filename, sizeof(img_filename), "%s/bst_%d.png", dir, change_number);

    // Создаем директорию, если она не существует
    system("mkdir -p bst_visual_log");

    // Генерация DOT-файла
    generate_akr_dot_log_file(root, dot_filename);

    // Генерация изображения с помощью Graphviz
    char command[512];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_filename, img_filename);
    system(command);
}