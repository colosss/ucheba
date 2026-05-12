#ifndef REPOSITORY_CAR_REPOSITORY_H
#define REPOSITORY_CAR_REPOSITORY_H

#include "domain/car.h"
#include "structures/hashtable.h"
#include <string>
#include <vector>

class CarRepository {
private:
    HashTable<Car> table;

public:
    CarRepository();

    bool add(const Car& car);
    bool update(const Car& car);
    bool remove(const std::string& number);
    Car* find(const std::string& number);
    const Car* find(const std::string& number) const;
    bool exists(const std::string& number) const;
    void clear();
    size_t size() const;

    std::vector<Car> getAll() const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

    void printStructure() const;
};

#endif
