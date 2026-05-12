#include "repository/car_repository.h"
#include <fstream>

CarRepository::CarRepository()
    : table(7, [](const Car& car) { return car.getNumber(); }) {}

bool CarRepository::add(const Car& car) { return table.insert(car); }
bool CarRepository::update(const Car& car) { return table.update(car); }
bool CarRepository::remove(const std::string& number) { return table.remove(number); }
Car* CarRepository::find(const std::string& number) { return table.find(number); }
const Car* CarRepository::find(const std::string& number) const { return table.find(number); }
bool CarRepository::exists(const std::string& number) const { return find(number) != nullptr; }
void CarRepository::clear() { table.clear(); }
size_t CarRepository::size() const { return table.size(); }
std::vector<Car> CarRepository::getAll() const { return table.toVector(); }

bool CarRepository::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;
    clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        Car car;
        if (Car::deserialize(line, car)) add(car);
    }
    return true;
}

bool CarRepository::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    for (const Car& car : getAll()) out << car.serialize() << '\n';
    return true;
}

void CarRepository::printStructure() const { table.printStructure(); }
