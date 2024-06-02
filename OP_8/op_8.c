//В символьной строке удалить все слова с четным номером
#include <stdio.h>
#define YES 1
#define NO 0
#define MAXLINE 1000

void process_line(char buffer[]);

int main(void){
    char line[MAXLINE];
    fgets(line, MAXLINE, stdin);
    process_line(line);
    puts(line);
    
    return 0;
}

void process_line(char buffer[]){
    char c; //текущий символ
    int flag;//флаг - признак слова
    int count;//счетчик, используется для определения
    //четности слова в строке
    char *in_ptr; //указатель на текущий символ входной строки
    char *out_ptr;//указатель на текущий символ выходной строки
    char *word_ptr;//указатель на начало слова
    
    
    flag = NO;
    count = 0;
    in_ptr = buffer;//устанавливаем указатели на первый
    //элемент массива
    out_ptr = buffer;
    word_ptr = buffer;

    
    do{
        c = *in_ptr; //берем текущий элемент из буфера
        if(c == ' ' || c == ',' || c == '.' || c == '\n' || c == '\0'){
            if(flag == YES){
                count++;
                if((count % 2) != 0){ //если слово нечетное, то сохраняем
                    while(word_ptr < in_ptr)//переписываем
                        //слово в выходную строку
                        *out_ptr++ = *word_ptr++;
                }
            }
            flag = NO;
            *out_ptr++ = c;
        }
        else{
            if(flag == NO)
                word_ptr = in_ptr;//запоминаем адрес начала слова
            flag = YES;
        }
        in_ptr++;//продвинуть указатель вперед на текущий символ
    }
    while(c != '\0');
}
