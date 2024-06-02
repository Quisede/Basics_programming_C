#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define MAXLINE 1000

//void test(char *line, int n, ...);

void test(char* line, int n, ...) {
    va_list ptr; //указатель на необязательные параметры
    va_start(ptr, n);//настраиваем указатель на первый необязательный параметр

    for (int i = 0; i < n; i++) {
        int word_num = va_arg(ptr, int);//получаем очередной номер удаляемого слова
        char* word_start = line;//ставим начало слова на начало строки
        int word_count = 1;
        while (word_count < word_num && *word_start != '\0') {
            if (*word_start == ' ') {
                word_count++;
            }
            word_start++;
        }

        if (*word_start == '\0')
            break;

        //поиск конца слова
        char* word_end = word_start;//ставим конец слова на его начало
        while (*word_end != ' ' && *word_end != '\0') {
            word_end++;
        }

        //удаление слова из строки
        int len = strlen(word_end) + 1;
        while (*word_end != '\0') {
            *word_start++ = *word_end++;
        }
        *word_start = '\0';
    }
    va_end(ptr);
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 
    printf("Введите строку:\n");
    char line[MAXLINE];
    fgets(line, MAXLINE, stdin);
    test(line, 1, 10);
    //puts(line);
    printf("Строка после изменения:\n %s\n", line);
    return 0;
}
