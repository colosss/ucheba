#include "rentalrecord.h"

RentalRecord::RentalRecord(string clientNumber, string carNumber, string rentalDate, string returnDate) {
    this->clientNumber = clientNumber;
    this->carNumber = carNumber;
    this->rentalDate = rentalDate;
    this->returnDate = returnDate;
}
RentalRecord::~RentalRecord() {cout << "Rental record for client " << clientNumber << " and car " << carNumber << " deleted." << endl;}