#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

struct str_ptrs {
    char *str_start;
    char *str_end;
};

char *file_to_buffer(FILE *oneginfp) {
    fseek(oneginfp, 0, SEEK_END);
    long fileSize = ftell(oneginfp); // получаем текущую позицию (размер файла)
    fseek(oneginfp, 0, SEEK_SET); // возвращаем указатель в начало файла

    // Выделяем память для буфера
    char *buffer = (char *)malloc(fileSize + 1); // +1 для завершающего нуля
    if (!buffer) {
        perror("No удалось выделить память");
        fclose(oneginfp); // Не забудьте закрыть файл, если он был открыт
        return NULL; // Возврат к коду ошибки
    }

    // Читаем файл в буфер
    size_t bytesRead = fread(buffer, 1, fileSize, oneginfp);
    buffer[bytesRead] = '\0'; // добавляем завершающий ноль для строк

    // Закрываем файл
    fclose(oneginfp);

    return buffer; 
}

int strs_in_buffer(char *buffer) {
    int str_count = 0;
    for (int j = 0; buffer[j] != '\0'; j++) {
        if (buffer[j] == '\n') {
            str_count++;
        }
    }

    return str_count + 1; // Возвращаем количество строк и одну для null
}

str_ptrs *strurct_ptrs_array(char *buffer, int strs_in_buffer) {
    str_ptrs *str_ptrs_ar = (str_ptrs *)malloc(strs_in_buffer * sizeof(str_ptrs));
    int i = 0;
    int for_last_str = 0;

    str_ptrs_ar[i].str_start = &buffer[0];
    //конец одной = неначало другой
    for (int j = 0; buffer[j] != '\0'; j++) {
        for_last_str = j;
        if (buffer[j] == '\n') {
            str_ptrs_ar[i].str_end = &buffer[j-1];
            if (buffer[j+1] != '\0') {
                str_ptrs_ar[i+1].str_start = &buffer[j+1];
            }
            i++;
        }
    }
    // обработка если псоледняя строка без /n
    if (buffer[for_last_str] != '\n') {
        str_ptrs_ar[i].str_end = &buffer[for_last_str];
    }

    return str_ptrs_ar;
}

int len_s (str_ptrs s1) {
    return s1.str_end - s1.str_start;
}

int max_string (str_ptrs s1, str_ptrs s2) {
    int lens1 = len_s(s1);
    int lens2 = len_s(s2);
    return lens1 > lens2 ? lens1 : lens2;
    
}

int str_compare(str_ptrs s1, str_ptrs s2) {
    int i = 0;
    int j = 0;

    while ((s1.str_start + i) != (s1.str_end) && !isalpha(*(s1.str_start + i))) {
        i++;
    }

    while ((s2.str_start + j) != (s2.str_end) && !isalpha(*(s2.str_start + j))) {
        j++;
    }

    for (int k = i, t = j; (k < max_string(s1, s2)) && (t < max_string(s1, s2)); k++, t++){
        if (*(s1.str_start + k) != *(s2.str_start + t)){
            return *(s1.str_start + k) - *(s2.str_start + t);
        }
        if ((*(s1.str_start + k) == *(s1.str_end)) || (*(s2.str_start + t) == *(s2.str_end))){
            return 0;
        }
    }
    return 0;
}

str_ptrs *string_swap(str_ptrs *spa, int index_1, int index_2, int len_list) {
    str_ptrs temp = spa[index_1];
    spa[index_1] = spa[index_2];
    spa[index_2] = temp;
    return spa;
}

str_ptrs *sort_func(str_ptrs *spa, int len_list) {
    int i = 0;
    int flag = 1;
    int diff_s = 0;
    while (flag == 1){
        flag = 0;
        for (int j = 0; j <= (len_list - i - 2); j++){
            diff_s = str_compare(spa[j], spa[j+1]);
            if(diff_s > 0){
                spa = string_swap(spa, j, j+1, len_list);
                flag = 1;
            }
        }
        i++;
    }
    return spa;
}

void spa_output(str_ptrs *spa, char *buffer, int len_list) {
    int count = 0;
    printf ("output: ");
    for (int i = 0; i < len_list; i++) {
        count = 0;
        while (spa[i].str_start + count != spa[i].str_end) {
            printf("%c", *(spa[i].str_start + count));
            count++;
        }
        printf("%c", *(spa[i].str_end));
        printf("\n");
    }
}

int main() {
    FILE *oneginfp = fopen("onegin.txt", "rb");
    if (!oneginfp) {
        perror("No удалось открыть файл");
        return -1;
    }
    char *buffer = file_to_buffer(oneginfp);
    int strs = strs_in_buffer(buffer);
    str_ptrs *spa = strurct_ptrs_array(buffer, strs);
    spa = sort_func(spa, strs);
    spa_output(spa, buffer, strs);
    return 0;
}