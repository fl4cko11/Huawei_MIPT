#include "list_funcs.h"
#include "list_visual.h"

static void generate_dot_log(my_list *list) {
    generate_image(list, list->change_number);
    list->change_number++;
}

static void list_verify(my_list *list) {
    assert(list != nullptr);

    if (list->name == nullptr) {
        fprintf(stderr, "[LIST %s] name_ptr_error\n", list->name);
        exit(-1);
    }

    if (list->data == nullptr) {
        fprintf(stderr, "[LIST %s] data_ptr_error\n", list->name);
        exit(-1);
    }

    if (list->data[0] != poisoned) {
        fprintf(stderr, "[LIST %s] 1st_not_poisoned\n", list->name);
        exit(-1); 
    } // чек фиктивности 0го элемента

    if (list->neighbours_indx == nullptr) {
        fprintf(stderr, "[LIST %s] neighs_struct_error\n", list->name);
        exit(-1);
    }
    
    if (list->neighbours_indx[0].ind_next != 0) {
        fprintf(stderr, "[LIST %s] 1st_cant_have_next\n", list->name);
        exit(-1);
    } //чек фиктивности

    if (list->neighbours_indx[0].ind_prev != 0) {
        fprintf(stderr, "[LIST %s] 1st_cant_have_prev\n", list->name);
        exit(-1);
    } //чек фиктивности

    if (list->FREE < 0) {
        fprintf(stderr, "[LIST %s] FREE_less_0_error\n", list->name);
        exit(-1);
    }

    if (list->data[list->FREE] != poisoned) {
        fprintf(stderr, "[LIST %s] list_overflow\n", list->name);
        exit(-1);
    }   
}

static void list_dump_and_verify(my_list *list) {
    list_verify(list);
    FILE *log = fopen(list->logname, "a");

    fprintf(log, "[LIST %s] list: ", list->name);
    for (int i = 0; i < list->size; i++) {
        fprintf(log, "%d ",list->data[i]);
    }
    fprintf(log, "\n");

    fprintf(log, "[LIST %s] next: ", list->name);
    for (int i = 0; i < list->size; i++) {
        fprintf(log, "%d ", list->neighbours_indx[i].ind_next);
    }
    fprintf(log, "\n");

    fprintf(log, "[LIST %s] prev: ", list->name);
    for (int i = 0; i < list->size; i++) {
        fprintf(log, "%d ", list->neighbours_indx[i].ind_prev);
    }
    fprintf(log, "\n");

    fprintf(log, "[LIST %s] next_free: ", list->name);
    for (int i = 0; i < list->size; i++) {
        fprintf(log, "%d ", list->neighbours_indx[i].next_free);
    }
    fprintf(log, "\n");

    fprintf(log, "[LIST %s] free: %d\n\n", list->name, list->FREE);

    fclose(log);
}

void list_ctor(my_list *list, const char *name, const char *logname, size_t size) {
    assert(name != nullptr);
    assert(logname != nullptr);
    assert(size > 0);

    FILE *log = fopen(logname, "w"); // чистим лог
    fprintf(log, "the zero element of this list is fictitious; when viewing the log, take the 1st index as zero\n");
    fclose(log);

    list->size = size + 1; // принимаем, что пользователь использует индексацию с нуля (для фиктивного 1 слот доп)
    list->name = name;
    list->logname = logname;
    list->data = (int *)calloc(list->size, sizeof(int));
    list->neighbours_indx = (neighbours_ind *)calloc(list->size, sizeof(neighbours_ind));
    list->neighbours_indx[0].ind_next = 0; // фиктивный
    list->neighbours_indx[0].ind_prev = 0; // фиктивный
    list->neighbours_indx[0].next_free = 0; // фиктивный
    list->neighbours_indx[1].ind_next = 0; // по умолчанию 1й элемент и фронт и бэк
    list->neighbours_indx[1].ind_prev = 0; // причём критерий фронта: прев - фиктивный, критерий бэка - некст фиктивный
    list->FREE = 1;
    list->change_number = 0;

    for (int i = 0; i < list->size; i++) {
        list->data[i] = poisoned; // 0й всегда фиктивный
    }

    for (int i = 2; i < list->size; i++) {
        list->neighbours_indx[i].ind_next = -1;
    }

    for (int i = 2; i < list->size; i++) {
        list->neighbours_indx[i].ind_prev = -1;
    }

    for (int i = 1; i < list->size - 1; i++) {
        list->neighbours_indx[i].next_free = i + 1;
    }
    list->neighbours_indx[list->size - 1].next_free = 1; // закольцовка

    list_dump_and_verify(list);
}

int *get_front_ptr(my_list *list) {
    list_verify(list);
    for (int i = 1; i < list->size; i++) {
        if (list->neighbours_indx[i].ind_prev == 0 && &list->data[i] != nullptr) {
            return &list->data[i];            
        }
    }
    fprintf(stderr, "cant find front\n");
    return nullptr;
}

int get_front_indx(my_list *list) {
    list_verify(list);
    for (int i = 1; i < list->size; i++) {
        if (list->neighbours_indx[i].ind_prev == 0) {
            return i;            
        }
    }
    return -1;
}

int *get_back_ptr(my_list *list) {
    list_verify(list);
    for (int i = 1; i < list->size; i++) {
        if (list->neighbours_indx[i].ind_next == 0 && &list->data[i] != nullptr) {
            return &list->data[i];            
        }
    }
    fprintf(stderr, "cant find back\n");
    return nullptr;
}

int get_back_indx(my_list *list) {
    list_verify(list);
    for (int i = 1; i < list->size; i++) {
        if (list->neighbours_indx[i].ind_next == 0) {
            return i;            
        }
    }
    return -1;
}

int get_user_anchor_unit_index_in_data(my_list *list, int user_index_anchor_unit) {
    int front_indx = get_front_indx(list);
    int indx_in_data_of_user_anchor_unit = front_indx;
    for (int j = 0; j < user_index_anchor_unit; j++) {
        indx_in_data_of_user_anchor_unit = list->neighbours_indx[indx_in_data_of_user_anchor_unit].ind_next;
        if (indx_in_data_of_user_anchor_unit == -1) {
            return -1;
        }
    }
    return indx_in_data_of_user_anchor_unit;
}

void push_front(my_list *list, int insert_unit) {
    list_verify(list);
    int front_indx = get_front_indx(list);
    if (front_indx == -1) {
        fprintf(stderr, "cant find front\n");
        exit(-1);
    }

    FILE *log = fopen(list->logname, "a");
    fprintf(log, "[LIST %s] PUSH_FRONT unit: %d (now front in data have index: %d)...\n", list->name, insert_unit, front_indx);
    fclose(log);

    int tmp = list->neighbours_indx[list->FREE].next_free; // в некст_фри валидного слота лежит следующее валидное для фри
    list->data[list->FREE] = insert_unit; // вставляем элемент по фри
    if (list->neighbours_indx[list->FREE].ind_next != list->neighbours_indx[list->FREE].ind_prev || list->neighbours_indx[list->FREE].ind_next == -1) {
        list->neighbours_indx[list->FREE].ind_next = front_indx; // следующим у вставленного становится предыдущий первый
        list->neighbours_indx[list->FREE].ind_prev = 0; // предыдущим у вставленного становится фиктивный, тк он первый
        list->neighbours_indx[front_indx].ind_prev = list->FREE; // у предыдущего первого предыдущим становится вставленный
    }
    list->FREE = tmp; // в некст валидного слота лежит следующее валидное для фри
    list_dump_and_verify(list);
    generate_dot_log(list);
}

void push_back(my_list *list, int insert_unit) {
    list_verify(list);
    int back_indx = get_back_indx(list);
    if (back_indx == -1) {
        fprintf(stderr, "cant find back\n");
        exit(-1);
    }

    FILE *log = fopen(list->logname, "a");
    fprintf(log, "[LIST %s] PUSH_BACK unit: %d (now back in data have index: %d)...\n", list->name, insert_unit, back_indx);
    fclose(log);

    int tmp = list->neighbours_indx[list->FREE].next_free; // в некст_фри валидного слота лежит следующее валидное для фри
    list->data[list->FREE] = insert_unit; // вставляем элемент по фри
    if (list->neighbours_indx[list->FREE].ind_next != list->neighbours_indx[list->FREE].ind_prev || list->neighbours_indx[list->FREE].ind_next == -1) {
        list->neighbours_indx[list->FREE].ind_next = 0; // следующим у вставленного становится фиктивный, тк он последний
        list->neighbours_indx[list->FREE].ind_prev = back_indx; // предыдущим у вставленного становится предыдущий последний
        list->neighbours_indx[back_indx].ind_next = list->FREE; // у предыдущего последнего следующим становится вставленный
    }
    list->FREE = tmp; // в некст валидного слота лежит следующее валидное для фри
    list_dump_and_verify(list);
    generate_dot_log(list);
}

void push_front_of_unit(my_list *list, int insert_unit, int user_index_anchor_unit) {
    list_verify(list);
    int index_anchor_unit = get_user_anchor_unit_index_in_data(list, user_index_anchor_unit);
    if (index_anchor_unit == -1) {
        fprintf(stderr, "no index: %d in list right now", index_anchor_unit);
        exit(-1);
    }

    FILE *log = fopen(list->logname, "a");
    fprintf(log, "[LIST %s] PUSH_FRONT_OF_UNIT: %d with index in data: %d\n", list->name, list->data[index_anchor_unit], index_anchor_unit);
    fclose(log);

    int tmp = list->neighbours_indx[list->FREE].next_free; // в некст_фри валидного слота лежит следующее валидное для фри
    list->data[list->FREE] = insert_unit;
    list->neighbours_indx[list->FREE].ind_next = index_anchor_unit; // у вставленного следующим становится якорный
    list->neighbours_indx[list->FREE].ind_prev = list->neighbours_indx[index_anchor_unit].ind_prev; // у вставленного предыдущим становится предыдущий якорного
    list->neighbours_indx[list->neighbours_indx[index_anchor_unit].ind_prev].ind_next = list->FREE; // у левого соседа прошлого правым становится вставленный
    list->neighbours_indx[index_anchor_unit].ind_prev = list->FREE; // у якорного следующим становится вставленный
    list->FREE = tmp; // в некст валидного слота лежит следующее валидное для фри
    list_dump_and_verify(list);
    generate_dot_log(list);
}

void push_back_of_unit(my_list *list, int insert_unit, int user_index_anchor_unit) {
    list_verify(list);
    int index_anchor_unit = get_user_anchor_unit_index_in_data(list, user_index_anchor_unit);
    if (index_anchor_unit == -1) {
        fprintf(stderr, "no index: %d in list right now", index_anchor_unit);
        exit(-1);
    }

    FILE *log = fopen(list->logname, "a");
    fprintf(log, "[LIST %s] PUSH_BACK_OF_UNIT: %d with index in data: %d\n", list->name, list->data[index_anchor_unit], index_anchor_unit);
    fclose(log);

    int tmp = list->neighbours_indx[list->FREE].next_free; // в некст_фри валидного слота лежит следующее валидное для фри
    list->data[list->FREE] = insert_unit;
    list->neighbours_indx[list->FREE].ind_next = list->neighbours_indx[index_anchor_unit].ind_next; // у вставленного следующим становится некст якороного
    list->neighbours_indx[list->FREE].ind_prev = index_anchor_unit; // у вставленного предыдущим становится якорный
    list->neighbours_indx[list->neighbours_indx[index_anchor_unit].ind_next].ind_prev = list->FREE; // у правого соседа якорного левым соседом становится вставленный 
    list->neighbours_indx[index_anchor_unit].ind_next = list->FREE; // у якорного следующим становится вставленный
    list->FREE = tmp; // в некст валидного слота лежит следующее валидное для фри
    list_dump_and_verify(list);
    generate_dot_log(list);
}

void delete_unit(my_list *list, int user_index_delete_unit) {
    list_verify(list);
    int index_delete_unit = get_user_anchor_unit_index_in_data(list, user_index_delete_unit);
    if (index_delete_unit == -1) {
        fprintf(stderr, "no index: %d in list right now", index_delete_unit);
        exit(-1);
    }

    FILE *log = fopen(list->logname, "a");
    fprintf(log, "[LIST %s] DELETE_UNIT: %d with index in data: %d\n", list->name, list->data[index_delete_unit], index_delete_unit);
    fclose(log);

    list_verify(list);
    list->data[index_delete_unit] = poisoned;
    list->neighbours_indx[list->neighbours_indx[index_delete_unit].ind_prev].ind_next = list->neighbours_indx[index_delete_unit].ind_next; // у левого соседа удаляемого предыдущим становится предыдущий удаленного
    list->neighbours_indx[list->neighbours_indx[index_delete_unit].ind_next].ind_prev = list->neighbours_indx[index_delete_unit].ind_prev; // у правого соседа удаляемого предыдущим становится предыдущий удаляемого
    list->neighbours_indx[index_delete_unit].next_free = list->FREE; // в некст удалённого сохраняем текущее значение фри для захвата его потом
    list->neighbours_indx[index_delete_unit].ind_next = -1;
    list->neighbours_indx[index_delete_unit].ind_prev = -1;
    list->FREE = index_delete_unit; // а сам фри указываем на удалённый слот
    list_dump_and_verify(list);
    generate_dot_log(list);
}

void list_dtor(my_list *list) {
    free(list->data);
    free(list->neighbours_indx);
}