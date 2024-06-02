#include <stdio.h>
#define N 10
int main(void)
{
    int x[N]; //создаем массив из N элементов
    int aver = 0; //среднее арифметическое элементов массива
    int i = 0; //i-ый элемент массива
    
    printf("Введите элементы массива\n");
    for(i = 0; i < N; i++)
    {
        printf("x[%d] = ", i);
        scanf("%d", &x[i]);
    }
    
    for(i = 0; i < N; i++)
        aver = aver + x[i];
    aver = aver / N;
    
    for(i = 0; i < N; i++)
    {
        if(x[i] < aver)
            x[i] = 0;
    }
    
    for(i = 0; i < N; i++)
        printf("%d ", x[i]);
    
    printf("\n");
    
    return 0;
}
