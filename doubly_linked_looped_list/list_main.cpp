#include "list_funcs.h"
#include "list_visual.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <full path to log_file>\n", argv[0]);
        return 1;
    }

    my_list list_vasya = {};
    list_ctor(&list_vasya, "vasya", argv[1], 8);

    for (int i = 1; i < 4; i++) {
        push_front(&list_vasya, i*i);
    }

    push_front_of_unit(&list_vasya, 777, 2);

    push_back_of_unit(&list_vasya, 333, 1);

    delete_unit(&list_vasya, 3);

    return 0;
}