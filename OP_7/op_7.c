#include <stdio.h>
int main(void)
{
    long z;
    unsigned long y;
    unsigned long mask;
    int pos;
    
    printf("z = ");
    scanf("%x", &z); // ввод в шестнадцатиричном формате
    
    y = (unsigned int)z;
    pos = -1;
    mask = 0x80000000;
    
    while (y != 0){
        pos++;
        if(y & mask){
            break;
        }
        y >>= 1;
    }
    if(pos < 0)
        printf("Старшая единица отсутствует\n");
    else
        printf("Старшая единица находится на позиции: %d\n", pos);
    
    return 0;
}
