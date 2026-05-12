#ifndef DOMAIN_CLIENT_H
#define DOMAIN_CLIENT_H

#include <string>

class Client {
private:
    std::string licenseNumber;
    std::string fullName;
    std::string passportData;
    std::string address;

public:
    Client() = default;
    Client(std::string licenseNumber, std::string fullName, std::string passportData, std::string address);

    const std::string& getLicenseNumber() const;
    const std::string& getFullName() const;
    const std::string& getPassportData() const;
    const std::string& getAddress() const;

    void setFullName(const std::string& value);
    void setPassportData(const std::string& value);
    void setAddress(const std::string& value);

    std::string serialize() const;
    static bool deserialize(const std::string& line, Client& outClient);
};

#endif
