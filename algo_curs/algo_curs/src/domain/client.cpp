#include "domain/client.h"
#include "utils/string_utils.h"

Client::Client(std::string licenseNumber, std::string fullName, std::string passportData, std::string address)
    : licenseNumber(std::move(licenseNumber)),
      fullName(std::move(fullName)),
      passportData(std::move(passportData)),
      address(std::move(address)) {}

const std::string& Client::getLicenseNumber() const { return licenseNumber; }
const std::string& Client::getFullName() const { return fullName; }
const std::string& Client::getPassportData() const { return passportData; }
const std::string& Client::getAddress() const { return address; }

void Client::setFullName(const std::string& value) { fullName = value; }
void Client::setPassportData(const std::string& value) { passportData = value; }
void Client::setAddress(const std::string& value) { address = value; }

std::string Client::serialize() const {
    return licenseNumber + "|" + sanitizeField(fullName) + "|" + sanitizeField(passportData) + "|" + sanitizeField(address);
}

bool Client::deserialize(const std::string& line, Client& outClient) {
    auto parts = split(line, '|');
    if (parts.size() != 4) return false;
    outClient = Client(trim(parts[0]), trim(parts[1]), trim(parts[2]), trim(parts[3]));
    return true;
}
