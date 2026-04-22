#include <iostream>
#include <cmath>


using namespace std;

int vvod (int razmer){
    int x;
    cin>>x;
    while (!cin.good() or (x>pow(2,razmer)-1) or x<0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Неправильно введено значение, повторите ввод\n ";
        cin>>x;
    }
    return x;
    
}


int main(){
    int a, b, d;

    short int x;

    cout<<"Введите значение B\n";
    b=vvod(3);
    cout<<"Введите значение A\n";
    a=vvod(3);
    cout<<"Введите значение D\n";
    d=vvod(1);
    
    x = 0 | b << 1 | a << 4 | d << 7 | 198<<8;
    cout <<hex <<x<<endl;
    return x;
}