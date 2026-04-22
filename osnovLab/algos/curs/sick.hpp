#include <iostream>
//hash tables

using namespace std;

class Sick {
public:
    Sick(string register_number, string name, int year_of_birth, string adress, string place_of_work){
        this->register_number = register_number;
        this->name = name;
        this->year_of_birth = year_of_birth;
        this->adress = adress;
        this->place_of_work = place_of_work;
    }
    ~Sick(){
        cout << "Destructor called for " << name << endl;
    }
    void create_register_number();

private:
    string register_number;
    string name;
    int year_of_birth;
    string adress;
    string place_of_work;

};