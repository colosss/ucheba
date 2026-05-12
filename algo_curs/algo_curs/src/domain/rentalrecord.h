#ifndef DOMAIN_RENTAL_RECORD_H
#define DOMAIN_RENTAL_RECORD_H

#include <string>

class RentalRecord {
private:
    std::string clientLicenseNumber;
    std::string carNumber;
    std::string issueDate;
    std::string returnDate;

public:
    RentalRecord() = default;
    RentalRecord(std::string clientLicenseNumber, std::string carNumber, std::string issueDate, std::string returnDate);

    const std::string& getClientLicenseNumber() const;
    const std::string& getCarNumber() const;
    const std::string& getIssueDate() const;
    const std::string& getReturnDate() const;

    std::string serialize() const;
    static bool deserialize(const std::string& line, RentalRecord& outRecord);
};

#endif
