#include "service/rental_service.h"
#include "utils/boyer_moore.h"
#include <filesystem>
#include <utility>

RentalService::RentalService(std::string dataDirectory) {
    if (!dataDirectory.empty() && dataDirectory.back() != '/' && dataDirectory.back() != '\\') {
        dataDirectory += "/";
    }
    std::filesystem::create_directories(dataDirectory);
    clientFile = dataDirectory + "client.txt";
    carFile = dataDirectory + "car.txt";
    rentalFile = dataDirectory + "rentals.txt";
}

OperationResult RentalService::saveAfterChange() {
    OperationResult result = save();
    if (!result.ok) return result;
    return {true, "Операция выполнена. Данные сохранены."};
}

void RentalService::syncCarAvailabilityWithRentals() {
    for (const RentalRecord& record : rentals.getAll()) {
        Car* car = cars.find(record.getCarNumber());
        if (car) car->setAvailable(false);
    }
}

OperationResult RentalService::load() {
    clients.loadFromFile(clientFile);
    cars.loadFromFile(carFile);
    rentals.loadFromFile(rentalFile);
    syncCarAvailabilityWithRentals();
    return {true, "Данные загружены."};
}

OperationResult RentalService::save() {
    bool okClients = clients.saveToFile(clientFile);
    bool okCars = cars.saveToFile(carFile);
    bool okRentals = rentals.saveToFile(rentalFile);
    if (!okClients || !okCars || !okRentals) return {false, "Не удалось сохранить один или несколько файлов данных."};
    return {true, "Данные сохранены."};
}

OperationResult RentalService::loadDemoData() {
    clients.clear();
    cars.clear();
    rentals.clear();

    clients.add(Client("10 АВ 100001", "Иванов Иван Иванович", "4010 123456, УВД Центрального района", "г. Москва, ул. Ленина, 10"));
    clients.add(Client("20 ЕК 100002", "Петров Петр Петрович", "4011 123457, УВД Северного района", "г. Москва, ул. Гагарина, 5"));
    clients.add(Client("30 МО 100003", "Сидорова Анна Сергеевна", "4012 123458, УВД Южного района", "г. Санкт-Петербург, Невский пр., 1"));
    clients.add(Client("40 НР 100004", "Кузнецов Алексей Игоревич", "4013 123459, УВД Западного района", "г. Казань, ул. Победы, 20"));
    clients.add(Client("50 СТ 100005", "Орлова Мария Павловна", "4014 123460, УВД Восточного района", "г. Москва, ул. Тверская, 7"));

    cars.add(Car("А123ВС-77", "Toyota", "Белый", 2018, false));
    cars.add(Car("В456ЕК-78", "Lada", "Черный", 2020, true));
    cars.add(Car("Е789МН-77", "BMW", "Синий", 2021, true));
    cars.add(Car("К111ОР-99", "Kia", "Серый", 2019, true));
    cars.add(Car("М222СТ-78", "Toyota", "Красный", 2022, false));
    cars.add(Car("Н333УХ-77", "Hyundai", "Белый", 2023, true));

    rentals.add(RentalRecord("10 АВ 100001", "А123ВС-77", "01.05.2026", "10.05.2026"));
    // М222СТ-78 имеет available=false и не находится в списке проката: это демонстрация ремонта.
    syncCarAvailabilityWithRentals();
    return saveAfterChange();
}

OperationResult RentalService::registerClient(const Client& client) {
    if (!clients.add(client)) return {false, "Клиент с таким номером водительского удостоверения уже существует."};
    return saveAfterChange();
}

OperationResult RentalService::removeClient(const std::string& licenseNumber) {
    if (!clients.exists(licenseNumber)) return {false, "Клиент не найден."};
    if (rentals.hasClientRental(licenseNumber)) return {false, "Нельзя снять клиента с обслуживания: у него есть выданный автомобиль."};
    clients.remove(licenseNumber);
    return saveAfterChange();
}

OperationResult RentalService::clearClients() {
    if (!rentals.empty()) return {false, "Нельзя очистить клиентов: есть активные записи проката."};
    clients.clear();
    return saveAfterChange();
}

const Client* RentalService::findClient(const std::string& licenseNumber) const { return clients.find(licenseNumber); }
std::vector<Client> RentalService::listClients() const { return clients.getAllInOrder(); }

std::vector<Client> RentalService::searchClientsByFragment(const std::string& fragment) const {
    std::vector<Client> result;
    if (fragment.empty()) return result;
    for (const Client& client : clients.getAllPostOrder()) { // вариант 1: обратный обход АВЛ-дерева
        if (BoyerMoore::contains(client.getFullName(), fragment) || BoyerMoore::contains(client.getAddress(), fragment)) {
            result.push_back(client);
        }
    }
    return result;
}

OperationResult RentalService::addCar(const Car& car) {
    if (!cars.add(car)) return {false, "Автомобиль с таким государственным номером уже существует."};
    return saveAfterChange();
}

OperationResult RentalService::removeCar(const std::string& carNumber) {
    const Car* car = cars.find(carNumber);
    if (!car) return {false, "Автомобиль не найден."};
    if (rentals.hasCarRental(carNumber)) return {false, "Нельзя удалить автомобиль: он выдан клиенту."};
    if (!car->isAvailable()) return {false, "Нельзя удалить автомобиль: он отмечен как отсутствующий или находится в ремонте."};
    cars.remove(carNumber);
    return saveAfterChange();
}

OperationResult RentalService::clearCars() {
    if (!rentals.empty()) return {false, "Нельзя очистить автомобили: есть активные записи проката."};
    cars.clear();
    return saveAfterChange();
}

const Car* RentalService::findCar(const std::string& carNumber) const { return cars.find(carNumber); }
std::vector<Car> RentalService::listCars() const { return cars.getAll(); }

std::vector<Car> RentalService::searchCarsByBrand(const std::string& brandFragment) const {
    std::vector<Car> result;
    if (brandFragment.empty()) return result;
    for (const Car& car : cars.getAll()) {
        if (BoyerMoore::contains(car.getBrand(), brandFragment)) result.push_back(car);
    }
    return result;
}

OperationResult RentalService::sendCarToRepair(const std::string& carNumber) {
    Car* car = cars.find(carNumber);
    if (!car) return {false, "Автомобиль не найден."};
    if (rentals.hasCarRental(carNumber)) return {false, "Нельзя отправить в ремонт: автомобиль выдан клиенту."};
    if (!car->isAvailable()) return {false, "Автомобиль уже отсутствует в бюро проката."};
    car->setAvailable(false);
    return saveAfterChange();
}

OperationResult RentalService::receiveCarFromRepair(const std::string& carNumber) {
    Car* car = cars.find(carNumber);
    if (!car) return {false, "Автомобиль не найден."};
    if (rentals.hasCarRental(carNumber)) return {false, "Автомобиль числится выданным клиенту, прибытие из ремонта невозможно."};
    car->setAvailable(true);
    return saveAfterChange();
}

OperationResult RentalService::rentCar(const std::string& clientLicense, const std::string& carNumber,
                                       const std::string& issueDate, const std::string& plannedReturnDate) {
    if (!clients.exists(clientLicense)) return {false, "Клиент не найден."};
    Car* car = cars.find(carNumber);
    if (!car) return {false, "Автомобиль не найден."};
    if (!car->isAvailable()) return {false, "Автомобиль отсутствует: он уже выдан или находится в ремонте."};
    if (rentals.hasCarRental(carNumber)) return {false, "Автомобиль уже выдан клиенту."};
    if (rentals.hasClientRental(clientLicense)) return {false, "У клиента уже есть выданный автомобиль."};

    car->setAvailable(false);
    rentals.add(RentalRecord(clientLicense, carNumber, issueDate, plannedReturnDate));
    return saveAfterChange();
}

OperationResult RentalService::returnCar(const std::string& clientLicense, const std::string& carNumber) {
    Car* car = cars.find(carNumber);
    if (!car) return {false, "Автомобиль не найден."};
    if (!rentals.removeByClientAndCar(clientLicense, carNumber)) return {false, "Запись проката для указанного клиента и автомобиля не найдена."};
    car->setAvailable(true);
    return saveAfterChange();
}

std::vector<RentalRecord> RentalService::listRentals() const { return rentals.getAll(); }
std::vector<RentalRecord> RentalService::rentalsByClient(const std::string& clientLicense) const { return rentals.findByClientLicense(clientLicense); }
const RentalRecord* RentalService::rentalByCar(const std::string& carNumber) const { return rentals.findByCarNumber(carNumber); }

void RentalService::printClientTree() const { clients.printStructure(); }
void RentalService::printCarHashTable() const { cars.printStructure(); }
void RentalService::printRentalList() const { rentals.printStructure(); }
