//C++
#include <iostream>
#include <fstream>
#include  <clocale>

//C
#include <stdio.h>
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#endif

using namespace std;

int maincpp(){
    ifstream intext("D://home//mifugi//Рабочий стол//osnovLab//podgotov//intext.txt");
    ofstream outext("D://home//mifugi//Рабочий стол//osnovLab//podgotov//outtext.txt");

    
}
int mainc(){

}

int main(){
    setlocale (LC_ALL, "rus");
    
}