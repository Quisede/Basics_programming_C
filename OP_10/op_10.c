#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define YES 1
#define NO 0
#define MAXLEN 1000 // максимальная длина строки
#define NLINES 1000 // максимальное число строк

//функция отражения строки
void mirror(char* lines_ptr) {
    char* start = lines_ptr;//указатель на начало слова
    char* end = lines_ptr;//указатель на конец слова
    
    while(*end){
        if(*end == ' ' || *end == '\n'){//если символ - пробел или конец строки, то значит слово закончилось, выставляем указатели
            char* word_start = start;//ставим указатель на первую букву слова
            char* word_end = end - 1;//ставим указатель на последнюю букву слова
            
            //меняем местами буквы в слове
            while(word_start <  word_end){
            char tmp = *word_start;
            *word_start = *word_end;
            *word_end = tmp;
            word_start++;
            word_end--;
            }
            start = end + 1;//выставляем начало строки на следующую букву слова
        }
        end++;//cдвигаем на следующий символ
    }
    
    //обработка последнего слова в строке
    char* word_start = start;//ставим указатель на первую букву
    char* word_end = end - 1;//ставим указатель на последнюю букву
    // Переворачиваем последнее слово
    while(word_start <  word_end){
    char tmp = *word_start;
    *word_start = *word_end;
    *word_end = tmp;
    word_start++;
    word_end--;
    }
    
    //переворачиваем всю строку
    char* line_start = lines_ptr;//на первый символ
    char* line_end = end - 1;//на последний символ
    while (line_start < line_end) {
    char temp = *line_start;
    *line_start = *line_end;
    *line_end = temp;
    line_start++;
    line_end--;
    }
}

int main(void) {
    FILE *fp;//входной файл
    char **lines_ptr = NULL;//указатель на динамический массив
    int npointers;//число указаталей в динамическом массиве
    int nlines = 0;//число строк в файле
    int count = 0;//кол-во итераций цикла
    int i;

    fp = fopen("lab_10.txt", "rt");//открываем файл
    if(fp == NULL){
        printf("Ошибка при открытии файла");
        return 0;
    }
    
    //заказываем и обнуляем динамический массив
    lines_ptr = (char**)calloc(NLINES, sizeof(char*));
    npointers = NLINES;
    
    //основной цикл чтения файла, пока не достигнем его конца
    while(!feof(fp)) {
        char line[MAXLEN];//массив для сохранения считанной строки
        char *ptr = fgets(line, MAXLEN, fp);//считываем строку из файла в массив line и присваиваем указатель
        if(ptr == NULL)
            break; //если не удалось прочитать
    
        int len = (int)strlen(line);//находим длину считанной строки
        
        // Удаление символа новой строки на первой итерации
        if (count == 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        
        //если число строк достигает достигает текущего выделенного объема, то расширяем динамический массив и заполняем новые ячейки нулями
        if(nlines == npointers) {
            npointers += NLINES;
            lines_ptr = (char**)realloc(lines_ptr, npointers * sizeof(char*) );
            memset(&lines_ptr[nlines], 0, NLINES * sizeof(char*));
        }
        //выделяем память под новую строчку, считываем новую из файла
        lines_ptr[nlines] = (char*)malloc(len+1);
        strcpy(lines_ptr[nlines], line);
        nlines++;
        count++;
    }
    //после прочтения всех строк вызываем функцию переворота строк и выводим на экран
    for(i = 0; i < nlines; i++) {
        mirror(lines_ptr[i]); // Переворачиваем слова в каждой строке
        printf("%s", lines_ptr[i]);
    }
    //обнуляем все выделенные массивы
    for(i = 0; i < nlines; i++) {
        if(lines_ptr[i] != NULL) free(lines_ptr[i]);
    }
    if(lines_ptr != NULL) free(lines_ptr);

    //закрываем файл
    fclose(fp);
    printf("\n");
    return 0;
}
