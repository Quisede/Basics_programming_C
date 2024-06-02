#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "bmp.h"
#define TEST_FILE "test_r.bmp"
#define DPM 0//1000

float ang = 0.00;//коэффициент наклона - в радианах

//структура которая содержит координаты обрабатываемой точки
struct Point
{

    float x;
    float y;
};

//функции нахождения центра
float CenterX(float new_ABCD[4][3]) 

{
    float centerX = (new_ABCD[0][0] + new_ABCD[1][0] + new_ABCD[2][0] + new_ABCD[3][0]) / 4;

    return centerX;
}

float CenterY(float new_ABCD[4][3]) 

{
    float centerY = (new_ABCD[0][1] + new_ABCD[1][1] + new_ABCD[2][1] + new_ABCD[3][1]) / 4;

    return centerY;
}

int main(void)
{
    //открытие конфигурационного файла
    FILE* file = fopen("config.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла");
        return 1;
    }
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;
    float ang_config;

    fscanf(file, "x1 = %d\n", &x1);
    fscanf(file, "y1 = %d\n", &y1);
    fscanf(file, "x2 = %d\n", &x2);
    fscanf(file, "y2 = %d\n", &y2);
    fscanf(file, "x3 = %d\n", &x3);
    fscanf(file, "y3 = %d\n", &y3);
    fscanf(file, "x4 = %d\n", &x4);
    fscanf(file, "y4 = %d\n", &y4);
    fscanf(file, "ang = %f\n", &ang_config);

    fclose(file);  // Закрываем файл

    // Далее вы можете использовать считанные значения переменных по своему усмотрению
    printf("x1 = %d\n", x1);
    printf("y1 = %d\n", y1);
    printf("x2 = %d\n", x2);
    printf("y2 = %d\n", y2);
    printf("x3 = %d\n", x3);
    printf("y3 = %d\n", y3);
    printf("x4 = %d\n", x4);
    printf("y4 = %d\n", y4);
    printf("ang = %f\n", ang_config);
    int ABCD[4][3] = { {x1, y1, 1},
        {x2, y2, 1},
        {x3, y3, 1},
        {x4, y4, 1} };//массив с координатами четырехуольника
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\n", ABCD[i][j]);
        }
    }

    int new_ABCD[4][3] = { {x1, y1, 1},
        {x2, y2, 1},
        {x3, y3, 1},
        {x4, y4, 1} };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\n", new_ABCD[i][j]);
        }
    }

    
    char filenames[20];
    for (int k = 0; k < 10; k++) {

        //rotate
        float centerX = (new_ABCD[0][0] + new_ABCD[1][0] + new_ABCD[2][0] + new_ABCD[3][0]) / 4;
        float centerY = (new_ABCD[0][1] + new_ABCD[1][1] + new_ABCD[2][1] + new_ABCD[3][1]) / 4;
        float out[4][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
        float matrix_translate[3][3] = { {1, 0, 0}, {0, 1, 0}, {-centerX, -centerY, 1} };
        float matrix_rotate[3][3] = { {cos(ang), sin(ang), 0}, {-sin(ang), cos(ang), 0}, {0, 0, 1} };
        float matrix_translate_back[3][3] = { {1, 0, 0}, {0, 1, 0}, {centerX, centerY, 1} };
        float tmp[4][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

        for (int i = 0; i < 4; i++) // ïåðåíîñ ê íà÷àëó êîîðäèíàò
            for (int j = 0; j < 3; j++)

            {
                out[i][j] = 0;

                for (int k = 0; k < 3; k++) {

                    out[i][j] += ABCD[i][k] * matrix_translate[k][j];

                }

            }

        for (int i = 0; i < 4; i++) // ïîâîðîò â íà÷àëå êîîðäèíàò

            for (int j = 0; j < 3; j++)

            {
                tmp[i][j] = 0;

                for (int k = 0; k < 3; k++) {

                    tmp[i][j] += out[i][k] * matrix_rotate[k][j];

                }

            }

        for (int i = 0; i < 4; i++) // ïåðåíîñ îáðàòíî
            for (int j = 0; j < 3; j++)

            {
                new_ABCD[i][j] = 0;

                for (int k = 0; k < 3; k++) {

                    new_ABCD[i][j] += tmp[i][k] * matrix_translate_back[k][j];

                }
            }
        int count = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                printf("new_ABCD_%d: %d\n", count, new_ABCD[i][j]);
                count++;
            }
        }
// Сортировка вершин по координате y
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (new_ABCD[i][1] > new_ABCD[j][1]) {
                    int tempX = new_ABCD[i][0];
                    int tempY = new_ABCD[i][1];
                    int tempZ = new_ABCD[i][2];
                    new_ABCD[i][0] = new_ABCD[j][0];
                    new_ABCD[i][1] = new_ABCD[j][1];
                    new_ABCD[i][2] = new_ABCD[j][2];
                    new_ABCD[j][0] = tempX;
                    new_ABCD[j][1] = tempY;
                    new_ABCD[j][2] = tempZ;
                }
            }
        }

        // Поменять местами последние две координаты
        int tempX = new_ABCD[2][0];
        int tempY = new_ABCD[2][1];
        new_ABCD[2][0] = new_ABCD[3][0];
        new_ABCD[2][1] = new_ABCD[3][1];
        new_ABCD[3][0] = tempX;
        new_ABCD[3][1] = tempY;


        FILE* fp;
        MY_BITMAPFILEHEADER bmfh;  // файловый заголовок
        MY_BITMAPINFOHEADER bmih;  // информационный заголовок

        BYTE* buffer;               // буфер для изображения
        RGB_PIXEL pixel;
        int bsize,                  // размер буфера
            res, i, j;
        int width,                  // ширина изображения
            height,                 // высота изображения
            bstride;                // размер одной строки
        int nr, nc;                 // размер прямоугольника

        width = 1500;               // задаем размер изображения
        height = 1100;               //

        // вычисляем размер строки с учетом выравнивания по 4 байта
        bstride = width * sizeof(RGB_PIXEL);
        if (bstride % 4)
            bstride += 4 - bstride % 4;

        // вычисляет размер динамического массива
        bsize = height * bstride;


        bmfh.bfType = 0x4D42;                       // тип BMP-файла!!!
        bmfh.bfOffBits = sizeof(bmfh) + sizeof(bmih); // смещение данных
        // относительно начала
        // файла                                                                                                               bmfh.bfSize    = bmfh.bfOffBits + bstride * height;  // размер файла



        memset(&bmih, 0, sizeof(bmih));  // обнуляем всю структуру
        bmih.biSize = sizeof(bmih);     // размер информационного заголовка
        bmih.biBitCount = 24;           // размер точки в битах (3 байта)
        bmih.biCompression = 0;      // компрессии нет!!!
        bmih.biHeight = height;           // ширина
        bmih.biWidth = width;             // высота
        bmih.biSizeImage = bsize;         // объем данных с учетом выравнивания
        bmih.biPlanes = 1;           // один слой!!!
        bmih.biXPelsPerMeter = DPM;       // плотность точек для печати
        bmih.biYPelsPerMeter = DPM;       // по горизонтали и вертикали

        buffer = (BYTE*)malloc(bsize);    // заказываем буффер

        sprintf(filenames, "new_%d.bmp", k);
        if ((fp = fopen(filenames, "wb")) == NULL)
            return;

        fwrite(&bmfh, sizeof(bmfh), 1, fp); // записываем в файл заголовки
        fwrite(&bmih, sizeof(bmih), 1, fp);

        // Заполнение фона серым цветом
        for (i = 0; i < height; i++)
        {
            BYTE* line = buffer + i * bstride;
            for (j = 0; j < width; j++)
            {
                line[j * 3 + 0] = 128; // Значение синего цвета
                line[j * 3 + 1] = 128; // Значение зеленого цвета
                line[j * 3 + 2] = 128; // Значение красного цвета
            }
        }
        pixel.r = 255;                         // цвет пикселя - красный
        pixel.g = 0;
        pixel.b = 0;
struct Point coords[4] = {
        {roundf(new_ABCD[0][0]), roundf(new_ABCD[0][1])}, 
        {roundf(new_ABCD[1][0]), roundf(new_ABCD[1][1])}, 
        {roundf(new_ABCD[2][0]), roundf(new_ABCD[2][1])}, 
        {roundf(new_ABCD[3][0]), roundf(new_ABCD[3][1])}  
        };
        // Запись повернутого четырехугольника в буфер
        for (i = 0; i < 4; i++)
        {
            BYTE* line = buffer + (int)new_ABCD[i][1] * bstride;
            int start = (int)new_ABCD[i][0] * 3;
            line[start + 0] = pixel.b;
            line[start + 1] = pixel.g;
            line[start + 2] = pixel.r;
        }

        int min_y = coords[0].y;
        int max_y = coords[0].y;
        for (int i = 1; i < 4; i++) {
            if (coords[i].y < min_y) {
                min_y = coords[i].y;
            }
            if (coords[i].y > max_y) {
                max_y = coords[i].y;
            }
            printf("\nmin_y = %d\n", min_y);
            printf("\nmax_y = %d\n", max_y);
            for (int y = min_y; y <= max_y; y++) {
                float crossing[4]; int cnt = 0;
                for (int i = 0; i < 4; i++) {
                    float x1 = coords[i].x;
                    float y1 = coords[i].y;
                    float x2 = coords[(i + 1) % 4].x;
                    float y2 = coords[(i + 1) % 4].y;
                    if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
                        float x = x1 + (y - y1) / (y2 - y1) * (x2 - x1);
                        crossing[cnt++] = x;
                    }
                }

                for (int i = 0; i < cnt - 1; i++) {
                    for (int j = i + 1; j < cnt; j++) {
                        if (crossing[i] > crossing[j]) {
                            float tmp = crossing[i];
                            crossing[i] = crossing[j];
                            crossing[j] = tmp;
                        }
                    }
                }

                for (int i = 0; i < cnt; i += 2) {
                    for (int x = crossing[i]; x <= crossing[i + 1]; x++) {
                        BYTE* line = buffer + y * bstride;
                        int start = x * 3;
                        line[start + 0] = pixel.b; // Значение синего цвета
                        line[start + 1] = pixel.g; // Значение зеленого цвета
                        line[start + 2] = pixel.r; // Значение красного цвета
                    }
                }
            }
        }

        fwrite(buffer, bsize, 1, fp);         // запись изображения в файл
        free(buffer);

        ang += ang_config;
    }
    return 0;
}
