// #include "iostream"
#include <iostream>
using namespace std;

class B1{
public:
    B1(){
        cout<<"Construtor B1 parametr = "<< b1 <<endl;
    }
    void set(int b1);
    int get();
    void showB1();
    ~B1(){
        cout<<"Destroi B1"<<endl;
    }
protected:
    int b1;
};

class B2{
public:
    B2(){
        b2=0;
        cout<<"Construtor B2 parametr = "<< b2 <<endl;
    }
    void set(int b2);
    int get();
    void showB2();
    ~B2(){
        cout<<"Destroi B2"<<endl;
    }
protected:
    int b2;
};



class D1: virtual private B1, virtual public B2 {
public:
    void showD1();
    D1(int _d1, int _b1, int _b2);
    ~D1(){
        cout<<"Destroi D1"<<endl;
    }
protected:
    int d1;
};
class D2: virtual public B1, virtual private B2 {
public:
    void showD2();
    D2(int _d2, int _b1, int _b2);
    ~D2(){
        cout<<"Destroi D2"<<endl;
    }

protected:
    int d2;
};

class D3: virtual private D1, virtual public D2{
public:
    void showD3();

    D3(int _d3, int _d1, int _d2, int _b1, int _b2);
    ~D3(){
        cout<<"Destroi D3"<<endl;
    }
protected:
    int d3;
};

