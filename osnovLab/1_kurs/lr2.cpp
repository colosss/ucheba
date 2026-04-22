#include <iostream>
#include <cmath>

using namespace std;



int main(){
    double x, y;
    try{
        cin.exceptions(istream::failbit | istream::badbit);
        cout<<"Введите значение Х\n";
        cin>>x;
        cout<<"Введите значение Y\n";
        cin>>y;
    }
    catch(istream::failure e)
    {
        cerr << "Введен неправильный тип данных\n";

    }
    if ((0<=y && y<=1 && -1 <=x && x<=1) or (y<0 && y>=-1 && (x*x+y*y)<=1 )){
        cout<<"Значения входят в диапазон";
    }
    
    // if ((0<=y<=1.0 && -1.0<=x<=1.0)||(0>y>=-1.0 && (x*x+y*y)<=1.0)){
    //     cout<<"Значения входят в диапазон";
    // }
    else cout<<"Значения вне диапазона";
}