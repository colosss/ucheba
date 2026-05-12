#include "car.h"

Car::Car(string number, string model, string color, int year, bool isAvilable) {
    this->number = number;
    this->model = model;
    this->color = color;
    this->year = year;
    this->isAvilable = isAvilable;
}
Car::~Car() {cout << "Car " << number << " deleted." << endl;}
