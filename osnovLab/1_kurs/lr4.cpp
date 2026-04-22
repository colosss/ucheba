#include <iostream>
#include <cmath>

using namespace std;


double vvod(char a){
    double i =0;
    cout<<"Введите "<<a<<endl;
    cin>>i;
    while (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Неправильно введено значение, повторите ввод\n ";
        cin>>i;
    }
    return i;

}


double func (double a, double b, double c, double x, double &er){
    if (x<0.6 and b+c!=0){
        return a*x*x*x+b*b+c;
    }
    else if (x>0.6 and b+c==0 and x!=c){
        return (x-a)/(x-c);
    }
    else if (c!=0 or a!=0){
        return x/c+x/a;
        
    }
    else {
        er=1;
        return 0;
    }
}

int main(){
    double a, b, c, f=0, x_nach, x_kon, dx, er=0;
    a=vvod('a');
    b=vvod('b');
    c=vvod('c');
    x_nach=vvod('n');
    x_kon=vvod('k');
    dx=vvod('d');
    while (x_nach>x_kon or dx<=0){
        cout<<"Error! Непраивильно введены n, k, d"<<endl;
        x_nach=vvod('n');
        x_kon=vvod('k');
        dx=vvod('d');
    }
    cout<<endl;
    for (double x=x_nach; x_nach<=x and x<=x_kon; x+=dx){
        
        if (er==0 ){
            f = func(a, b, c, x, er);
            cout<<"x: "<<x<<"\t"<<"y: "<<f<<endl;
        }
        else{
            cout<<"Error"<<endl;
        }
    }

}