#include <stdio.h>
#define YES 1
#define NO 0
#define MAXLINE 100
void process_line(char buffer[]);
int main(void)
{
    char line[MAXLINE];
    
    fgets(line, 100, stdin);
    process_line(line);
    puts(line);
    return 0;
}

void process_line(char buffer[])
{
    char c; //текущий символ
    int flag; //признак слова
    int found; //идентификатор обнаружения числа
    int i; //позиция текущего символа исходной строки
    int pos; //позиция текущего символа результирующей строки
    int start;  //позиция начала слова
    int j;
    
    flag = NO;
    found = NO;
    i = 0;
    pos = 0;
    start = 0;
    
    do
    {
        c = buffer[i];//вносим в переменную c первый символ массива
        if(c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\0')
        {
            if(flag == YES)
            {
                if(found == NO)
                {
                    for(j = start; j < i; j++)
                        buffer[pos++]=buffer[j];
                }
            }
            flag = NO;
            buffer[pos++] = c;
        }
        else
        {
            if(flag == NO)
                start = i;
            if(c >= '0' && c <= '9')
                found = YES;
            else
                found = NO;
            flag = YES;
        }
        i++;
    }
    while( c != '\0');
}
