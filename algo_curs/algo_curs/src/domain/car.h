#ifndef DOMAIN_CAR_H
#define DOMAIN_CAR_H

#include <string>

class Car {
private:
    std::string number;
    std::string brand;
    std::string color;
    int year = 0;
    bool available = true;

public:
    Car() = default;
    Car(std::string number, std::string brand, std::string color, int year, bool available);

    const std::string& getNumber() const;
    const std::string& getBrand() const;
    const std::string& getColor() const;
    int getYear() const;
    bool isAvailable() const;

    void setBrand(const std::string& value);
    void setColor(const std::string& value);
    void setYear(int value);
    void setAvailable(bool value);

    std::string serialize() const;
    static bool deserialize(const std::string& line, Car& outCar);
};

#endif
