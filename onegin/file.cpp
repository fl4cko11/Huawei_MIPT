#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int words_in_txt(FILE *txt_file) {
    char str[20];
    int count = 0;

    // Считываем слова из файла
    while (fscanf(txt_file, "%19s", str) == 1) {  // Ограничиваем чтение до 19 символов + '\0'
        count++;
    }

    // Возвращаем указатель в начало файла для повторного чтения
    rewind(txt_file);
    return count;
}

int main() {
    FILE *oneginfp = fopen("onegin.txt", "r");
    if (oneginfp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int words_onegin = words_in_txt(oneginfp);

    // Выделяем память для массива строк
    char **str_list = (char **)malloc(words_onegin * sizeof(char *));
    if (str_list == NULL) {
        perror("Failed to allocate memory for string list");
        fclose(oneginfp);
        return 1;
    }

    for (int i = 0; i < words_onegin; i++) {
        str_list[i] = (char *)malloc(20 * sizeof(char)); // Выделяем память для каждой строки
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
    for (int i = 0; i < words_onegin; i++) {
        fscanf(oneginfp, "%19s", str_list[i]);  // Ограничиваем чтение до 19 символов
    }

    // Выводим слова
    for (int i = 0; i < words_onegin; i++) {
        printf("%s\n", str_list[i]);  // Добавляем перевод строки для лучшей читаемости
        free(str_list[i]);  // Освобождаем память для каждой строки
    }

    free(str_list);  // Освобождаем память для массива указателей
    fclose(oneginfp);  // Закрываем файл

    return 0;
}