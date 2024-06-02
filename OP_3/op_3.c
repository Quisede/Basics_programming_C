#include <stdio.h>
#define IN 1
#define OUT 0
int main (void)
{
    int c; // текущий символ из потока
    int counter; // счетчик, сколько слов состоит из более чем N букв
    int flag; // признак слова
    int N; // количество букв, которое ввел пользователь
    int Q; // количество букв в исследуемом слове
    
    counter = 0;
    flag = OUT;
    Q = 0;
    
    printf("Введите число N \n");
    scanf("%d", &N);
    
    while((c=getchar()) != EOF)
    {
        if(c == ' ' || c == '.' || c == ',' || c == '\n')
        {
            if(flag == IN)
            {
                if(Q >= N)
                {
                    counter++;
                }
            }
            Q = 0;
            flag = OUT;
        }
        else
        {
            flag = IN;
            Q++;
        }
    }
    printf("number of words = %d\n", counter );
    return 0;
}
