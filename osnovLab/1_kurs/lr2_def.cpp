#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double x=0;
    double y=0;
    cout<<"Введите значение Х\n";
    cin>>x;
    cout<<"Введите значение Y\n";
    cin>>y;
    if ((0<=y && y<=1 && -1 <=x && x<=1) or (y<0 && y>=-1 && (x*x+y*y)<=1 )){
        cout<<"Значения входят в диапазон\n";
    }
    else cout<<"Значения вне диапазона\n";
}