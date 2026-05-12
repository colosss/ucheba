#include "domain/car.h"
#include "utils/string_utils.h"
#include <cstdlib>

Car::Car(std::string number, std::string brand, std::string color, int year, bool available)
    : number(std::move(number)), brand(std::move(brand)), color(std::move(color)), year(year), available(available) {}

const std::string& Car::getNumber() const { return number; }
const std::string& Car::getBrand() const { return brand; }
const std::string& Car::getColor() const { return color; }
int Car::getYear() const { return year; }
bool Car::isAvailable() const { return available; }

void Car::setBrand(const std::string& value) { brand = value; }
void Car::setColor(const std::string& value) { color = value; }
void Car::setYear(int value) { year = value; }
void Car::setAvailable(bool value) { available = value; }

std::string Car::serialize() const {
    return number + "|" + sanitizeField(brand) + "|" + sanitizeField(color) + "|" + std::to_string(year) + "|" + (available ? "1" : "0");
}

bool Car::deserialize(const std::string& line, Car& outCar) {
    auto parts = split(line, '|');
    if (parts.size() != 5) return false;
    int parsedYear = std::atoi(parts[3].c_str());
    bool parsedAvailable = trim(parts[4]) == "1" || toLowerAscii(trim(parts[4])) == "true";
    outCar = Car(trim(parts[0]), trim(parts[1]), trim(parts[2]), parsedYear, parsedAvailable);
    return true;
}
