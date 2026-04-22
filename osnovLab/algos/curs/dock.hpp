#include <iostream>
//AVL TREESS
using namespace std;

class Dock{
public:
    Dock(string name, string type, int number_of_cabinet, string schedule){
        this->name = name;
        this->type = type;
        this->number_of_cabinet = number_of_cabinet;
        this->schedule = schedule;
    }
    ~Dock(){
        cout << "Destructor called for " << name << endl;
    }
private:
    string name;
    string type;
    int number_of_cabinet;
    string schedule;
};