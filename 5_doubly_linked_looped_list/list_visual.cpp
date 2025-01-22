#include "list_visual.h"

void generate_dot_file(my_list *list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == nullptr) {
        fprintf(stderr, "cant open dot file\n");
        exit(-1);
    }
    
    fprintf(file, "digraph G {\n");
    
    for (int i = 1; i < list->size; i++) {
        if (&list->data[i] != nullptr && list->data[i] != poisoned) {  // Проверка, что узел существует
            fprintf(file, "    n%d [label=\"%d\"];\n", i, list->data[i]);

            if (list->neighbours_indx[i].ind_next != -1) { // если есть следующий
                fprintf(file, "    n%d -> n%d;\n", i, list->neighbours_indx[i].ind_next);
            }
            
            if (list->neighbours_indx[i].ind_prev != -1) { // если есть предыдущий
                fprintf(file, "    n%d -> n%d;\n", i, list->neighbours_indx[i].ind_prev);
            }
        }
    }
    
    fprintf(file, "}\n");
    fclose(file);
}

void generate_image(my_list *list, int change_number) {
    char dot_filename[256];
    char img_filename[256];
    const char *dir = "list_visual_log"; // Директория для сохранения

    // Формируем имена файлов с указанием пути
    snprintf(dot_filename, sizeof(dot_filename), "%s/list_%d.dot", dir, change_number);
    snprintf(img_filename, sizeof(img_filename), "%s/list_%d.png", dir, change_number);

    // Создаем директорию, если она не существует
    system("mkdir -p list_visual_log"); // -p (создать если не существует)

    // Генерация DOT-файла
    generate_dot_file(list, dot_filename);

    // Генерация изображения с помощью Graphviz
    char command[512];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_filename, img_filename);
    system(command);
}
