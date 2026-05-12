#include "domain/rentalrecord.h"
#include "utils/string_utils.h"

RentalRecord::RentalRecord(std::string clientLicenseNumber, std::string carNumber, std::string issueDate, std::string returnDate)
    : clientLicenseNumber(std::move(clientLicenseNumber)),
      carNumber(std::move(carNumber)),
      issueDate(std::move(issueDate)),
      returnDate(std::move(returnDate)) {}

const std::string& RentalRecord::getClientLicenseNumber() const { return clientLicenseNumber; }
const std::string& RentalRecord::getCarNumber() const { return carNumber; }
const std::string& RentalRecord::getIssueDate() const { return issueDate; }
const std::string& RentalRecord::getReturnDate() const { return returnDate; }

std::string RentalRecord::serialize() const {
    return clientLicenseNumber + "|" + carNumber + "|" + sanitizeField(issueDate) + "|" + sanitizeField(returnDate);
}

bool RentalRecord::deserialize(const std::string& line, RentalRecord& outRecord) {
    auto parts = split(line, '|');
    if (parts.size() != 4) return false;
    outRecord = RentalRecord(trim(parts[0]), trim(parts[1]), trim(parts[2]), trim(parts[3]));
    return true;
}
