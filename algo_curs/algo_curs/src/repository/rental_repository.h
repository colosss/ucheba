#ifndef REPOSITORY_RENTAL_REPOSITORY_H
#define REPOSITORY_RENTAL_REPOSITORY_H

#include "domain/rentalrecord.h"
#include "structures/cyclic_doubly_list.h"
#include <string>
#include <vector>

class RentalRepository {
private:
    CyclicDoublyList<RentalRecord> list;
    void sortByCarNumber();

public:
    bool add(const RentalRecord& record);
    bool removeByCarNumber(const std::string& carNumber);
    bool removeByClientAndCar(const std::string& clientLicense, const std::string& carNumber);

    RentalRecord* findByCarNumber(const std::string& carNumber);
    const RentalRecord* findByCarNumber(const std::string& carNumber) const;
    std::vector<RentalRecord> findByClientLicense(const std::string& clientLicense) const;
    bool hasClientRental(const std::string& clientLicense) const;
    bool hasCarRental(const std::string& carNumber) const;

    void clear();
    size_t size() const;
    bool empty() const;
    std::vector<RentalRecord> getAll() const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

    void printStructure() const;
};

#endif
