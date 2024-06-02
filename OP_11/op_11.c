#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

//функция для нахождения макроимени в тексте
bool is_macro_name(const char *word, const char *all_macro_names) {
    int i, j;
    //сравниваем слово из массива с макросами и обрабатываемое слово из файла
    for(i = 0; all_macro_names[i] != '\0'; i++) {
        for(j = 0; word[j] != '\0'; j++) {
            if (all_macro_names[i + j] != word[j]) {
                break; // Если символы не совпадают, прерываем внутренний цикл.
            }
        }
        //если дошли до конца обрабатываемого слова и до этого все совпадало
        //реализуем доп проверки:
        //1)дошли до конца слова word
        //2)найденное слово - не конец другого слова
        //3)найденное слово - не начало другого слова
        if(word[j] == '\0'
            && (i == 0 || all_macro_names[i - 1] == ' ')
            && (all_macro_names[i + j] == '\0' || all_macro_names[i + j] == ' ')) {
            return true; // Если мы дошли до конца слова `word`, значит нашли макроимя.
        }
    }
    return false;
}


//основная функция
int main(void) {
    HANDLE hStdout;//дескриптор консольного окна
    FILE *fp;//входной файл
    int i;
    int current_char; //текущий элемент

    // Массив для хранения всех макроимен
    char all_macro_names[1000] = {0};
    int all_macro_names_len = 0;//длина

    WORD foregroundColor0; //обычный цвет слов
    WORD foregroundColor1;//красный цвет слов
    WORD foregroundColor;//цвет символа
    WORD backgroundColor;//цвет фона
    WORD textAttribute;//атрибут текста - цвет символа и фона

    // Получить стандартный дескриптор
    hStdout= GetStdHandle (STD_OUTPUT_HANDLE) ;

    // определить цвета символов, разделителей и фона
    foregroundColor0 = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;//белый
    foregroundColor1 = FOREGROUND_INTENSITY | FOREGROUND_RED;//красный

    SetConsoleTextAttribute (hStdout, foregroundColor0 | backgroundColor );
    SetConsoleOutputCP(65001);//поддержка UTF-8(для русского языка)

    //открытие файл, в случае неудачи - уведомление об ошибке
    fp = fopen("text_of_programm.txt", "rt");
    if(fp == NULL){
        printf("Ошибка при открытии файла");
        return -1;
    }

    //цикл нахождения макроимен после их объявления (т.е. после #define)
    while ((current_char = fgetc(fp)) != EOF) {
        if (current_char == '#') { //если нашел первый признак - #
            int next_char = fgetc(fp);//считываем следующий символ

            if (next_char == 'd') { //если нашел второй признак - d
                do { //значит находимся в #define
                    next_char = fgetc(fp); //берем слеюущие элементы пока не упремся в пробел или в "\" чт
                    //о говорит о многострочном объявлении
                } while (next_char != EOF && (!isspace(next_char) || (!isspace(next_char) && next_char != '\\')));


                // Выводим имена макроимен с подсветкой (красным цветом)
                int macro_name_len = 0; //длина массива с макроименами
                char macro_name[256]; //массив с макроименами  предназначенный для временного хранения одного макроимени,
                //которое в данный момент считывается
                //для многострочного объявления
                next_char = fgetc(fp);
                if(next_char == '\\'){
                    next_char = fgetc(fp);
                    next_char = fgetc(fp);
                }

                //заносим найдейнные макроимена в специальный массив
                while (next_char != EOF && (!isspace(next_char) || (!isspace(next_char) && next_char != '\\'))) {
                    macro_name[macro_name_len++] = (char) next_char;
                    next_char = fgetc(fp);
                }

                // Сохраняем имя макроса, разделяя имена пробелами
                if (all_macro_names_len > 0) {
                    all_macro_names[all_macro_names_len++] = ' ';
                }

                strcpy(&all_macro_names[all_macro_names_len], macro_name); //копируем из временного массива
                //в постоянный для макроимен
                all_macro_names_len += macro_name_len;
            }
        }
    }

    fclose(fp); //закрываем файл найдя все макроимена

    // Заново открываем файл для чтения уже для полноценного вывода в терминал
    fp = fopen("text_of_programm.txt", "rt");
    if(fp == NULL){
        printf("Ошибка при открытии файла");
        return -1;
    }

    while ((current_char = fgetc(fp)) != EOF) {
        // Читаем слово
        //ниже реализована защита от нахождения макроимени в символьной строке,
        //в комментариях (как однострочных, так и многострочных)
        if(current_char == '"'){
            int next_char = fgetc(fp);
            putchar(current_char);
            putchar(next_char);
            next_char = fgetc(fp);
            while(next_char != '"'){
                putchar(next_char);
                next_char = fgetc(fp);
            }

        }
        else if (current_char == '/') {
            int next_char = fgetc(fp);
            if (next_char == '/') {
                putchar(current_char);
                putchar(next_char);
                while ((current_char = fgetc(fp)) != '\n' && current_char != EOF) {
                    putchar(current_char);
                }
            } else if (next_char == '*') {
                // Обработка многострочных комментариев /* ... */
                putchar(current_char);
                putchar(next_char);
                int prev_char = next_char;
                while ((current_char = fgetc(fp)) != EOF) {
                    putchar(current_char);
                    if (prev_char == '*' && current_char == '/') {
                        break;
                    }
                    prev_char = current_char;
                }
            } else {
                putchar(current_char);
                // Если символ не является частью комментария, возвращаем его в файл
                ungetc(next_char, fp);
            }
        }
            else if (isalpha(current_char)) {
            char word[256];
            int word_len = 0;

            while (isalnum(current_char) || current_char == '_') {
                word[word_len++] = (char) current_char;
                current_char = fgetc(fp);
            }

            word[word_len] = '\0';

            if (is_macro_name(word, all_macro_names)) {
                // установить цвет символа
                foregroundColor = foregroundColor1;
                textAttribute = foregroundColor;
                SetConsoleTextAttribute (hStdout, textAttribute );
                printf("%s", word);
                // установить цвет символа
                foregroundColor = foregroundColor0;
                textAttribute = foregroundColor;
                SetConsoleTextAttribute (hStdout, textAttribute );
            } else {
                printf("%s", word);
            }
        }

        if (current_char != EOF) {
            putchar(current_char);
        }
    }

    fclose(fp);
    return 0;
}

/*
//функция для нахождения макроимени в тексте
bool is_macro_name(const char *word, const char *all_macro_names) {
    const char *match = strstr(all_macro_names, word); //ищет макроимя в строке
    return match != NULL && (match == all_macro_names || isspace((unsigned char) *(match - 1))) &&
           ((unsigned char) *(match + strlen(word)) == '\0' || isspace((unsigned char) *(match + strlen(word))));
}*/
