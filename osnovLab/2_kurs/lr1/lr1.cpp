#include "lr1.hpp"

using namespace std;

void yravnenie::setk(double _k){
    yravnenie::k=_k; 
}

void yravnenie::setb(double _b){
    yravnenie::b=_b;
}
void yravnenie::setx(double _x){
    yravnenie::x=_x;
}

double yravnenie::Root(){
    return k*x+b;
}
double yravnenie::getk(){
    return yravnenie::k;
}

double yravnenie::getb(){
    return yravnenie::b;
}
double yravnenie::getx(){
    return yravnenie::x;
}

int main(){
    yravnenie y1;
    y1.setb(10);
    y1.setk(6);
    y1.setx(1);
    cout<<"B = "<<y1.getb()<<" K = "<<y1.getk()<<" X = "<<y1.getx()<<  endl;
    cout<<"Yravnenie y=kx+b : y=";
    if (y1.getk()<0)cout<<"("<<y1.getk()<<")";
    else cout<<y1.getk();
    cout<<"*";
    if(y1.getx()<0)cout<<"("<<y1.getx()<<")";
    else cout<<y1.getx();
    if (y1.getb()>=0) cout<<"+";
    cout<<y1.getb()<<endl;
    cout<<"Otevet = "<<y1.Root()<<endl;
    cout<<endl;

    y1.setb(-1.521);
    y1.setk(-4.312);
    y1.setx(0);
    cout<<"B = "<<y1.getb()<<" K = "<<y1.getk()<<" X = "<<y1.getx()<<  endl;
    cout<<"Yravnenie y=kx+b : y=";
    if (y1.getk()<0)cout<<"("<<y1.getk()<<")";
    else cout<<y1.getk();
    cout<<"*";
    if(y1.getx()<0)cout<<"("<<y1.getx()<<")";
    else cout<<y1.getx();
    if (y1.getb()>=0) cout<<"+";
    cout<<y1.getb()<<endl;
    cout<<"Otevet = "<<y1.Root()<<endl;
    cout<<endl;

    y1.setb(0);
    y1.setk(0);
    y1.setx(-31.213);
    cout<<"B = "<<y1.getb()<<" K = "<<y1.getk()<<" X = "<<y1.getx()<<  endl;
    cout<<"Yravnenie y=kx+b : y=";
    if (y1.getk()<0)cout<<"("<<y1.getk()<<")";
    else cout<<y1.getk();
    cout<<"*";
    if(y1.getx()<0)cout<<"("<<y1.getx()<<")";
    else cout<<y1.getx();
    if (y1.getb()>=0) cout<<"+";
    cout<<y1.getb()<<endl;
    cout<<"Otevet = "<<y1.Root()<<endl;
    cout<<endl;
}