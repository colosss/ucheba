// Написать программу, которая считывает текст из файла и записывает в другой файл
// только те предложения, которые не содержат запятых.

#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <string.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    FILE* f1 = fopen("./files/input_text.txt", "r");
    FILE* f2 = fopen("./files/output_text.txtS", "w");
    if (!f1) {
        cout << "Ошибка при открытии файла text1.txt" << endl;
        exit(1);
    }
    if (!f2) {
        cout << "Ошибка при открытии файла result1.txt" << endl;
        exit(1);
        fclose(f1);
    }
    char l;
    bool f = 0;
    string mas;

    while ((l = fgetc(f1)) != EOF) {
        l = fgetc(f1);
        int s = 0;
        while (l != '.') {
            if (l == ',') f = 1;
            mas += l;
            l = fgetc(f1);
            if (l == '.') mas += l;
            s++;
        }
        if (s > 0) {
            if (f == 0 and l == '.') {
                fprintf(f2, "%s", mas.c_str());

                mas = "";
            }
            else {
                f = 0;
                mas = "";
            }
        }
    }

    fclose(f1);
    fclose(f2);
}