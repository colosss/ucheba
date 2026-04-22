#include "lr5.hpp"


void B1::set(int _b1){
    b1=_b1;
    cout<<"Seter B1 parametr = "<< b1 <<endl;

}
void B2::set(int _b2){
    b2=_b2;
    cout<<"Seter B2 parametr = "<< b2 <<endl;
}

void B1::showB1(){
    cout<<"B1 = "<<b1<<endl;
}
int B1::get(){
    return b1;
}

void B2::showB2(){
    cout<<"B2 = "<<b2<<endl;
}
int B2::get(){
    return b2;
}
void D1::showD1(){
    cout<<"D1 = "<<d1<<endl;
    B1::showB1();
    B2::showB2();
}
void D2::showD2(){
    cout<<"D2 = "<<d2<<endl;
    B1::showB1();
    B2::showB2();
}
void D3::showD3(){
    cout<<"D3 = "<<d3<<endl;
    D1::showD1();
    D2::showD2();
}


D1::D1(int _d1, int _b1, int _b2){
    B1::set(_b1);
    B2::set(_b2);
    d1=_d1;
    cout<<"Construtor D1 parametr = "<< d1 <<endl;
}

D2::D2(int _d2, int _b1, int _b2){
    B1::set(_b1);
    B2::set(_b2);
    d2=_d2;
    cout<<"Construtor D2 parametr = "<< d2 <<endl;
}

D3::D3(int _d3, int _d1, int _d2, int _b1, int _b2): D1(_d1, _b1, _b2), D2(_d2, _b1, _b2){
    d3=_d3;
    cout<<"Construtor D3 parametr = "<< d3 <<endl;
}

int main(){
    D3 d_3(303, 101, 202, 10, 20);
    d_3.showD3();
    cout<<endl;


}