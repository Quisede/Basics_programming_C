#include <stdio.h>
#define K 3 //строки
#define N 3 //столбцы

int main(void)
{
    int arr[K][N]; //основной массив
    int i, j, s, tmp, smin, smax, min_index, max_index; // i, j - переменные для работы с массивом; s, smin, smax - суммы элементов строк; min_index, max_index - индексы подходящих строк
    
    smin = 0;
    smax = 0;
    min_index = 0;
    max_index = 0;

    //ввод массива
    for(i = 0; i < K; i++)
        for(j = 0; j < N; j++)
            scanf("%d", &arr[i][j]);
    
    //вывод введенного массива
    printf("\n");
    for( i = 0; i < K; i++ )
        {
             for( j = 0; j < N; j++ )
                 printf("%4d ", arr[i][j]);
             printf("\n");
        }
    
    //поиск минамальной и максимальной суммы элементов строки и нахождение индекса этих строк
    for(i = 0; i < K; i++){
        s = 0;
        for(j = 0; j < N; j++)
            s += arr[i][j];
        if( i == 0)
            smin = smax = s;
        else if(s < smin){
            smin = s;
            min_index = i;
        }
        else if(s > smax){
            smax = s;
            max_index = i;
        }
    }
    
// замена местами нужных строк
    for(j = 0; j < N; j++){
        tmp = arr[min_index][j];
        arr[min_index][j] = arr[max_index][j];
        arr[max_index][j] = tmp;
    }
        
    //вывод получившегося массива
    printf("\n");
    for( i = 0; i < K; i++ )
        {
             for( j = 0; j < N; j++ )
                 printf("%4d ", arr[i][j]);
             printf("\n");
        }
    
    return 0;
}
