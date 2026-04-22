#include <iostream>
#include <cmath>

using namespace std;



double rad(double grad){

    double rad;
    rad = (grad * M_PI)/180;
    return rad;
    
}

int main(){
    string a1;
    double a, z1, z2, c;
    try{
        //cin.exceptions(istream::failbit | istream::badbit);
        cout<<"Введите а\n";
        cin>>a1;
        a=stoi(a1);
        c =rad(a);
        if ((1 + cos(4*c))==0||(1+cos(2*c))==0||tan((3./2)*M_PI - c)==0){
            cerr<<"Деление на 0";
            return 0;
        }
        z1=(sin(4*c)/ (1 + cos(4*c))) *(cos(2*c)/(1+cos(2*c)));
        z2=1./tan((3./2)*M_PI - c);
        cout<<"Z1: "<<z1<<endl;
        cout<<"Z2: "<<z2<<endl;
        
        //throw "Division by zero!";

    }
    // catch(istream::failure e)
    // {
    //     cerr << "Введен неправильный тип данных\n";

    // }
    catch(std::invalid_argument){
        cerr << "Введен неправильный тип данных\n";
    }
}