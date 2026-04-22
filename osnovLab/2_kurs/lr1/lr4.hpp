#include <iostream>

using namespace std;

class Base_figur{
protected:
    string name;
    int x0;
    int y0;
    int l;
    void proverka(int &l);
public:
    
    void print_info(double ploshad, double perimetr);
};

class Kvadrat : public Base_figur{
public:
    Kvadrat(){
        name="Kvadrat";
        x0=0;
        y0=0;
        l=1;
    }
    Kvadrat(int _x0, int _y0, int _l){
        name = "Kvadrat";
        x0=_x0;
        y0=_y0;
        l=_l;
        proverka(l);
    }
    double ploshad();
    double perimetr();
};

class Crug : public Base_figur{
public:
    Crug(){
        name="Crug";
        x0=0;
        y0=0;
        l=1;
    }
    Crug(int _x0, int _y0, int _l){
        name="Crug";
        x0=_x0;
        y0=_y0;
        l=_l;
    }
    double ploshad();
    double perimetr();

};

void Base_figur::proverka(int &l){
    if (l<=0) l=1;
}