#include <iostream>

class yravnenie{
private:
    double k=0;
    double b=0;
    double x=0;
public: 
    void setk(double _k);
    void setb(double _b);
    void setx(double _x);
    double getk();
    double getb();
    double getx();
    double Root();
};