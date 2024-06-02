#include <stdio.h>
#include <math.h> // подключение мат. библиотеки для работы функции "fabs"
int main(void)
{
    float s; // сумма ряда
    float x; // входной параметр ряда
    float a; // очередной элемент ряда
    float c; // числитель очередного элемента ряда
    float eps; // пороговое значение
    float b; // знаменатель очередного ряда элемента
    int count; // счетчик для факториала
    
    printf("eps = ");
    scanf("%f", &eps);
    printf("x = ");
    scanf("%f", &x);
    
    c = 1;
    b = 1;
    s = 0;
    a = c/b;
    count = 1;
    
    while(fabs(a) > eps)
    {
        s = s + a;
        c = c*x;
        b = b*(count);
        count++;
        a = c/b;
    }
    printf("s = %6.2f\n", s);
    return 0;
}
