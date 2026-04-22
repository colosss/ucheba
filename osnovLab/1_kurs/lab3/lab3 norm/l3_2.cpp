#include <iostream>
#include <cmath>
using namespace std;

unsigned short int vvod_2(){
    unsigned short int x;
    cin>>hex>>x;
    while (!cin.good() or x>65535)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Неправильно введено значение, повторите ввод\n ";
        cin>>hex>>x;
    }
    return x;
}


using namespace std;

int main(){
    unsigned short int x;
    cout<<"Введите 16 значение"<<endl;
    x=vvod_2();
    unsigned short int y = (x>>1)&0x7;
    cout<<"B: "<<dec<<y<<endl;
    y = (x>>4)&0x7;
    cout<<"A: "<<dec<<y<<endl;
    y = (x>>7)&0x1;
    cout<<"D: "<<dec<<y<<endl;
    return 0;

}