#include <iostream>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

class error_no_negative: public exception{
    public:
    error_no_negative(){}
    ~error_no_negative(){}
    const char* what() const noexcept override{
        return "No negative elements";
    }
};

class error_invalid_index: public exception{
    public:
    error_invalid_index(){}
    ~error_invalid_index(){}
    const char* what() const noexcept override{
        return "Invalid index";
    }
};

class error: public exception{
    public:
    error(const string & message):message{message}
    {}
    const char* what() const noexcept override{
        return message.c_str();
    }
    private:
    string message;

};

class Massiv {
public:
    Massiv(){
        n=12;
        m=new double[n];
        zapolnenie_mass();
    }
    Massiv(int _n, string _name){
        if (_n<12) throw error("Invalid n");
        n=_n;
        name=_name;
        m= new double [n];
        zapolnenie_mass();
    }
    Massiv& operator=(const Massiv& other) {
        if (this == &other) return *this;
        delete[] m;
        n = other.n;
        m = new double[n];
        for (int i=0;i<n;++i) m[i] = other.m[i];
        return *this;
    }
    ~Massiv(){
        delete[] m;
        cout<<"Destroy massiv "<<name<<endl;
    }

    int getN();
    void func1();
    void func2();
    void massiv_1();
    double get_element(int index);
    void print();
    void zapolnenie_mass();
    void primitive_fill();
    void set_name(string _name);
    void set_element(int index, double a);
private:
    int n;
    double *m;
    string name;
};