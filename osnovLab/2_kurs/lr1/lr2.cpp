#include <iostream>

#include "lr2.hpp"

using namespace std;

bool Crug::check_position(){
    if (((Crug::x0+Crug::x)*(Crug::x0+Crug::x)) + (Crug::y0+Crug::y)*(Crug::y0+Crug::y) <= (Crug::r0 * Crug::r0)) return 1;
    else return 0;
}

void Crug::otvet(){
    cout<<"Crug, centr cotorogo naoditca po coordinatam x0 = "<<Crug::x0<<", y0 = "<<Crug::y0<<", c radiusom r0 = "<< Crug::r0<<endl;
    cout<<"Coordinati tochki: x = "<<Crug::x<<", y = "<<Crug::y<<endl;
    if (Crug::check_position())cout<<"Otvet, tochka vhodit"<<endl;
    else cout<<"Otvet, tochka ne vhodit"<<endl;

    cout<<endl;
}

int main(){
    
    Crug c(1,1,5,2,2);
    Crug c0;
    Crug c1(c0);

    c.otvet();
    c0.otvet();
    c1.otvet();
    
}