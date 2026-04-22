#include <iostream>
using namespace std;

class Crug{
private:
    double x0;
    double y0;
    double r0;
    double x;
    double y;
public:
    Crug (){
        x0=2;
        y0=2;
        r0=1;
        x=4;
        y=4;
    }
    Crug(double _x0, double _y0, double _r0, double _x, double _y){
        x0=_x0;
        y0=_y0;
        r0=_r0;
        x=_x;
        y=_y;
    }

    Crug(const Crug &crug){
        x0= crug.x0;
        y0= crug.y0;
        r0= crug.r0;
        x=crug.x;
        y=crug.y;
    }
    ~Crug(){
        cout<<"Destroid Michail Crug"<<endl;
    }
    bool check_position();
    void otvet();
};