#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

using namespace std;

template <typename T>
class Massiv {
public:
    Massiv<T>(vector<T> & vec, int const size): data(vec), size(size){};
    ~Massiv(){
        cout << "Destructor called" << endl;
    };
    void print();
    double func1();
    void func2();
    void func3();

    private:
    vector<T> data;
    int const size;
};