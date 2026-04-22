#include <iostream>
#include "lr4.hpp"
using namespace std;



double Kvadrat::ploshad(){
    return (l*l);
}
double Kvadrat::perimetr(){
    return (l*4);
}


double Crug::ploshad(){
    return(3.14*l*l);
}
double Crug::perimetr(){
    return(3.14*2*l);
}
void Base_figur::print_info(double ploshad, double perimetr){
    string a;
    if (Base_figur::name == "Kvadrat") a="Dlina storoni: ";
    else a="Radius: ";
    cout<<"Coordinati figuri "<<Base_figur::name<<": ("<<Base_figur::x0<<", "<<Base_figur::y0<<")\n"<<a<<Base_figur::l<<" Ploshad: "<<ploshad<< " Perimtr: "<<perimetr<<endl<<endl;
}

int main(){

    Kvadrat kvad1;
    Kvadrat kvad2(0, 1, 10);
    Crug crug1;
    Crug crug2( 1, 20, 20);
    kvad1.print_info(kvad1.ploshad(), kvad1.perimetr());
    kvad2.print_info(kvad2.ploshad(), kvad2.perimetr());

    crug1.print_info(crug1.ploshad(),crug1.perimetr());
    crug2.print_info(crug2.ploshad(),crug2.perimetr());



}