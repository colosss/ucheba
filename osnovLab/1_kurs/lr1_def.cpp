#include <iostream>
#include <cmath>

using namespace std;

double rad(double grad){

    double rad;
    rad = (grad * M_PI)/180;
    return rad;
    
}

int main(){
    double a=0;
    double z1=0;
    double z2=0;
    double c =0;
    cout<<"Введите а\n";
    cin>>a;
    c =rad(a);
    if ((1 + cos(4*c))==0||(1+cos(2*c))==0||tan((3./2)*M_PI - c)==0){
        cerr<<"Деление на 0";
        return 0;
    }
    z1=(sin(4*c)/ (1 + cos(4*c))) *(cos(2*c)/(1+cos(2*c)));
    z2=1./tan((3./2)*M_PI - c);
    cout<<"Z1: "<<z1<<endl;
    cout<<"Z2: "<<z2<<endl;

}