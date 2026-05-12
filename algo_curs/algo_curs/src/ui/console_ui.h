#ifndef UI_CONSOLE_UI_H
#define UI_CONSOLE_UI_H

#include "service/rental_service.h"
#include <string>

class ConsoleUI {
private:
    RentalService service;

    static void printLine();
    static std::string readLine(const std::string& prompt);
    static int readInt(const std::string& prompt);
    static void waitEnter();
    static void printResult(const OperationResult& result);

    std::string readLicense();
    std::string readCarNumber();

    void printClient(const Client& client) const;
    void printCar(const Car& car) const;
    void printRental(const RentalRecord& record) const;

    void clientsMenu();
    void carsMenu();
    void rentRepairMenu();
    void structuresMenu();

    void registerClient();
    void removeClient();
    void listClients();
    void clearClients();
    void findClientByLicense();
    void searchClientsByFragment();

    void addCar();
    void removeCar();
    void listCars();
    void clearCars();
    void findCarByNumber();
    void searchCarsByBrand();

    void sendCarToRepair();
    void receiveCarFromRepair();
    void rentCar();
    void returnCar();
    void listRentals();

public:
    explicit ConsoleUI(const std::string& dataDirectory);
    void run();
};

#endif
