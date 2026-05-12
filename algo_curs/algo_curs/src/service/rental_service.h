#ifndef SERVICE_RENTAL_SERVICE_H
#define SERVICE_RENTAL_SERVICE_H

#include "domain/car.h"
#include "domain/client.h"
#include "domain/rentalrecord.h"
#include "repository/car_repository.h"
#include "repository/client_repository.h"
#include "repository/rental_repository.h"
#include <string>
#include <vector>

struct OperationResult {
    bool ok = false;
    std::string message;
};

class RentalService {
private:
    ClientRepository clients;
    CarRepository cars;
    RentalRepository rentals;

    std::string clientFile;
    std::string carFile;
    std::string rentalFile;

    OperationResult saveAfterChange();
    void syncCarAvailabilityWithRentals();

public:
    explicit RentalService(std::string dataDirectory);

    OperationResult load();
    OperationResult save();
    OperationResult loadDemoData();

    OperationResult registerClient(const Client& client);
    OperationResult removeClient(const std::string& licenseNumber);
    OperationResult clearClients();
    const Client* findClient(const std::string& licenseNumber) const;
    std::vector<Client> listClients() const;
    std::vector<Client> searchClientsByFragment(const std::string& fragment) const;

    OperationResult addCar(const Car& car);
    OperationResult removeCar(const std::string& carNumber);
    OperationResult clearCars();
    const Car* findCar(const std::string& carNumber) const;
    std::vector<Car> listCars() const;
    std::vector<Car> searchCarsByBrand(const std::string& brandFragment) const;

    OperationResult sendCarToRepair(const std::string& carNumber);
    OperationResult receiveCarFromRepair(const std::string& carNumber);
    OperationResult rentCar(const std::string& clientLicense, const std::string& carNumber,
                            const std::string& issueDate, const std::string& plannedReturnDate);
    OperationResult returnCar(const std::string& clientLicense, const std::string& carNumber);

    std::vector<RentalRecord> listRentals() const;
    std::vector<RentalRecord> rentalsByClient(const std::string& clientLicense) const;
    const RentalRecord* rentalByCar(const std::string& carNumber) const;

    void printClientTree() const;
    void printCarHashTable() const;
    void printRentalList() const;
};

#endif
