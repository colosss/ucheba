#include "repository/rental_repository.h"
#include <fstream>
#include <iostream>

void RentalRepository::sortByCarNumber() {
    list.shakerSort([](const RentalRecord& left, const RentalRecord& right) {
        return left.getCarNumber() < right.getCarNumber();
    });
}

bool RentalRepository::add(const RentalRecord& record) {
    if (hasCarRental(record.getCarNumber())) return false;
    list.pushBack(record);
    sortByCarNumber();
    return true;
}

bool RentalRepository::removeByCarNumber(const std::string& carNumber) {
    return list.removeIf([&](const RentalRecord& record) { return record.getCarNumber() == carNumber; });
}

bool RentalRepository::removeByClientAndCar(const std::string& clientLicense, const std::string& carNumber) {
    return list.removeIf([&](const RentalRecord& record) {
        return record.getClientLicenseNumber() == clientLicense && record.getCarNumber() == carNumber;
    });
}

RentalRecord* RentalRepository::findByCarNumber(const std::string& carNumber) {
    return list.findIf([&](const RentalRecord& record) { return record.getCarNumber() == carNumber; });
}

const RentalRecord* RentalRepository::findByCarNumber(const std::string& carNumber) const {
    return list.findIf([&](const RentalRecord& record) { return record.getCarNumber() == carNumber; });
}

std::vector<RentalRecord> RentalRepository::findByClientLicense(const std::string& clientLicense) const {
    return list.findAllIf([&](const RentalRecord& record) { return record.getClientLicenseNumber() == clientLicense; });
}

bool RentalRepository::hasClientRental(const std::string& clientLicense) const {
    return list.anyIf([&](const RentalRecord& record) { return record.getClientLicenseNumber() == clientLicense; });
}

bool RentalRepository::hasCarRental(const std::string& carNumber) const {
    return list.anyIf([&](const RentalRecord& record) { return record.getCarNumber() == carNumber; });
}

void RentalRepository::clear() { list.clear(); }
size_t RentalRepository::size() const { return list.size(); }
bool RentalRepository::empty() const { return list.empty(); }
std::vector<RentalRecord> RentalRepository::getAll() const { return list.toVector(); }

bool RentalRepository::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;
    clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        RentalRecord record;
        if (RentalRecord::deserialize(line, record)) add(record);
    }
    sortByCarNumber();
    return true;
}

bool RentalRepository::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    for (const RentalRecord& record : getAll()) out << record.serialize() << '\n';
    return true;
}

void RentalRepository::printStructure() const {
    list.printStructure([](const RentalRecord& record) { return record.getCarNumber(); });
}
