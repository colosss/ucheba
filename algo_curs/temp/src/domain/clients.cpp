#include "clients.h"

Client::Client(string name, string passport, string address, string number) {
    this->name = name;
    this->passport = passport;
    this->address = address;
    this->number = number;
}
Client::~Client() {cout << "Client " << name << " deleted." << endl;}
