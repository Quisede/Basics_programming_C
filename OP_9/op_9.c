#include <stdio.h>
#define MAXLINE 1024

int main(void) {
    FILE *fpin;
    FILE *fpout;

    char line[MAXLINE];//массив с обрабатываемой строкой
    char *ptr;

    fpin = fopen("text_op_lab.txt", "rt");
    if (fpin == NULL) {
        perror("Не удается открыть файл");
        return 1;
    }

    fpout = fopen("result.txt", "wt");
    if (fpout == NULL) {
        perror("Не удается открыть файл");
        return 1;
    }

    while (!feof(fpin)) {
        ptr = fgets(line, MAXLINE, fpin);

        if (ptr == NULL)
            break;

        char *line_ptr = line;//указатели для работы с входной строкой
        char *fline_ptr = line;
        int space_found = 0;// флаг (нахождение пробела)

        while (*line_ptr != '\0') {
            if (*line_ptr == ' ') {
                if (space_found == 0) {
                    *fline_ptr = *line_ptr;
                    fline_ptr++;
                    space_found = 1;
                }
            } else {
                *fline_ptr = *line_ptr;
                fline_ptr++;
                space_found = 0;
            }
            line_ptr++;
        }

        *fline_ptr = '\0';//ставим в конце терминальный ноль
        fputs(line, fpout);//выводим обработанную строку в выходной файл
    }

    fclose(fpin);  // закрыть входной файл
    fclose(fpout); // закрыть выходной файл

    return 0;
}
