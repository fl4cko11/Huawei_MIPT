#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

const int len_onegin = 20;
const int max_word = 100;

int max_string (char *s1, char *s2){
    int lens1 = strlen(s1);
    int lens2 = strlen(s2);
    return lens1 > lens2 ? lens1 : lens2;
    
}

int find_index(int *value_list, int value_for_s, int len_list){
    for (int i = 0; i < len_list; ++i) {
        if (value_list[i] == value_for_s) {
            return i;
        }
    }
    return -1;
}

int string_compare(char *s1, char *s2){
    for (int i = 0; i < max_string(s1, s2); i++){
        if (s1[i] != s2[i]){
            return s1[i] - s2[i];
        }
        if ((s1[i] == '\0') || (s2[i] == '\0')){
            return 0;
        }
    }
}

int *string_replacer(int *value_list, int value_for_s1, int value_for_s2, int diff_s, int len_list){
    int index_s1 = find_index(value_list, value_for_s1, len_list);
    int index_s2 = find_index(value_list, value_for_s2, len_list);

    if (diff_s > 0){
        int temp = value_list[index_s1];
        value_list[index_s1] = value_list[index_s2];
        value_list[index_s2] = temp;
        return value_list;
    return value_list;
    }
}

int *sort_func(int *value_list, char **string_list, int len_lists){ /*bubble*/
    int i = 0;
    int flag = 1;
    int diff_s;
    while (flag == 1){
        flag = 0;
        for (int j = 0; j <= (len_lists - i - 2); j++){
            diff_s = string_compare(string_list[j], string_list[j+1]);
            if(diff_s > 0){
                value_list = string_replacer(value_list, j, j+1, diff_s, len_lists);
                flag = 1;
            }
        }
        i++;
    }
    return value_list;
}

void sorted_string_list_print(int *sorted_value_list, char **string_list, int len_lists){
    for (int i = 0; i < len_lists; i++){
        printf("%s\n", string_list[sorted_value_list[i]]);
    }
}

int strings_in_txt(FILE *txt_file) {
    char str[len_onegin];
    int count = 0;
    // Считываем слова из файла
    while (fscanf(txt_file, "%[^\n]", str) == 1) {
        count++;
    }
    // Возвращаем указатель в начало файла для повторного чтения
    rewind(txt_file);
    return count;
}

int main(){
    FILE *oneginfp;
    oneginfp=fopen("onegin.txt", "r");
    if (oneginfp == NULL){
        perror("file wrong open");
        return 1;
    }

    int strings_onegin = strings_in_txt(oneginfp);
    printf("words in file: %d\n", strings_onegin);
    // Выделяем память для массива строк
    char **str_list = (char **)malloc(strings_onegin * sizeof(char *));
    if (str_list == NULL) {
        perror("Failed to allocate memory for string list");
        fclose(oneginfp);
        return 1;
    }

    for (int i = 0; i < strings_onegin; i++) {
        str_list[i] = (char *)malloc(max_word * sizeof(char)); // Выделяем память для каждой строки
        if (str_list[i] == NULL) {
            perror("Failed to allocate memory for a word");
            // Освобождаем уже выделенную память в случае ошибки
            for (int j = 0; j < i; j++) {
                free(str_list[j]);
            }
            free(str_list);
            fclose(oneginfp);
            return 1;
        }
    }

    // Считываем слова в массив строк
    for (int i = 0; i < strings_onegin; i++) {
        fscanf(oneginfp, "%s", str_list[i]);
    }

    int *value_list = (int *)malloc(strings_onegin * sizeof(int));
    for (int i = 0; i < strings_onegin; i++){
        value_list[i] = i;
    }

    int *sorted_val = sort_func(value_list, str_list, strings_onegin);
    sorted_string_list_print(sorted_val, str_list, strings_onegin);
    return 0;
}