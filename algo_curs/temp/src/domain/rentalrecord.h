#include <iostream>

using namespace std;

class RentalRecord {
private:
    string clientNumber;
    string carNumber;
    string rentalDate;
    string returnDate;
public:
    RentalRecord(string clientNumber, string carNumber, string rentalDate, string returnDate) {}
    ~RentalRecord() {}
};  