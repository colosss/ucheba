#include "ui/console_ui.h"
#include "utils/string_utils.h"
#include "utils/validation.h"
#include <iostream>
#include <limits>

ConsoleUI::ConsoleUI(const std::string& dataDirectory) : service(dataDirectory) {}

void ConsoleUI::printLine() {
    std::cout << "***************************************************" << std::endl;
}

std::string ConsoleUI::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return trim(value);
}

int ConsoleUI::readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int value = 0;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Введите число." << std::endl;
    }
}

void ConsoleUI::waitEnter() {
    std::cout << "Нажмите Enter для продолжения...";
    std::string ignored;
    std::getline(std::cin, ignored);
}

void ConsoleUI::printResult(const OperationResult& result) {
    std::cout << (result.ok ? "OK: " : "Ошибка: ") << result.message << std::endl;
}

std::string ConsoleUI::readLicense() {
    while (true) {
        std::string input = readLine("Номер водительского удостоверения (RR AA NNNNNN): ");
        std::string normalized, error;
        if (normalizeDriverLicense(input, normalized, error)) return normalized;
        std::cout << "Ошибка: " << error << std::endl;
    }
}

std::string ConsoleUI::readCarNumber() {
    while (true) {
        std::string input = readLine("Государственный номер (ANNNAA-NN): ");
        std::string normalized, error;
        if (normalizeCarNumber(input, normalized, error)) return normalized;
        std::cout << "Ошибка: " << error << std::endl;
    }
}

void ConsoleUI::printClient(const Client& client) const {
    std::cout << "ВУ: " << client.getLicenseNumber() << std::endl;
    std::cout << "ФИО: " << client.getFullName() << std::endl;
    std::cout << "Паспорт: " << client.getPassportData() << std::endl;
    std::cout << "Адрес: " << client.getAddress() << std::endl;
}

void ConsoleUI::printCar(const Car& car) const {
    std::cout << "Госномер: " << car.getNumber() << std::endl;
    std::cout << "Марка: " << car.getBrand() << std::endl;
    std::cout << "Цвет: " << car.getColor() << std::endl;
    std::cout << "Год выпуска: " << car.getYear() << std::endl;
    std::cout << "Наличие: " << (car.isAvailable() ? "да" : "нет") << std::endl;
}

void ConsoleUI::printRental(const RentalRecord& record) const {
    std::cout << "Клиент ВУ: " << record.getClientLicenseNumber()
              << ", автомобиль: " << record.getCarNumber()
              << ", дата выдачи: " << record.getIssueDate()
              << ", дата возврата: " << record.getReturnDate() << std::endl;
}

void ConsoleUI::run() {
    service.load();
    bool running = true;
    while (running) {
        printLine();
        std::cout << "Бюро проката автомобилей" << std::endl;
        std::cout << "1 - Клиенты" << std::endl;
        std::cout << "2 - Автомобили" << std::endl;
        std::cout << "3 - Прокат и ремонт" << std::endl;
        std::cout << "4 - Служебный просмотр структур" << std::endl;
        std::cout << "5 - Сохранить данные" << std::endl;
        std::cout << "6 - Загрузить демонстрационные данные" << std::endl;
        std::cout << "0 - Выход" << std::endl;
        int choice = readInt("Выбор: ");
        switch (choice) {
            case 1: clientsMenu(); break;
            case 2: carsMenu(); break;
            case 3: rentRepairMenu(); break;
            case 4: structuresMenu(); break;
            case 5: printResult(service.save()); waitEnter(); break;
            case 6: printResult(service.loadDemoData()); waitEnter(); break;
            case 0: running = false; printResult(service.save()); break;
            default: std::cout << "Некорректный пункт меню." << std::endl; waitEnter(); break;
        }
    }
}

void ConsoleUI::clientsMenu() {
    bool running = true;
    while (running) {
        printLine();
        std::cout << "Клиенты" << std::endl;
        std::cout << "1 - Регистрация нового клиента" << std::endl;
        std::cout << "2 - Снятие клиента с обслуживания" << std::endl;
        std::cout << "3 - Просмотр всех клиентов" << std::endl;
        std::cout << "4 - Очистка данных о клиентах" << std::endl;
        std::cout << "5 - Поиск клиента по номеру ВУ" << std::endl;
        std::cout << "6 - Поиск клиента по фрагменту ФИО или адреса" << std::endl;
        std::cout << "0 - Назад" << std::endl;
        int choice = readInt("Выбор: ");
        switch (choice) {
            case 1: registerClient(); break;
            case 2: removeClient(); break;
            case 3: listClients(); break;
            case 4: clearClients(); break;
            case 5: findClientByLicense(); break;
            case 6: searchClientsByFragment(); break;
            case 0: running = false; break;
            default: std::cout << "Некорректный пункт меню." << std::endl; waitEnter(); break;
        }
    }
}

void ConsoleUI::carsMenu() {
    bool running = true;
    while (running) {
        printLine();
        std::cout << "Автомобили" << std::endl;
        std::cout << "1 - Добавление нового автомобиля" << std::endl;
        std::cout << "2 - Удаление сведений об автомобиле" << std::endl;
        std::cout << "3 - Просмотр всех автомобилей" << std::endl;
        std::cout << "4 - Очистка данных об автомобилях" << std::endl;
        std::cout << "5 - Поиск автомобиля по госномеру" << std::endl;
        std::cout << "6 - Поиск автомобиля по марке" << std::endl;
        std::cout << "0 - Назад" << std::endl;
        int choice = readInt("Выбор: ");
        switch (choice) {
            case 1: addCar(); break;
            case 2: removeCar(); break;
            case 3: listCars(); break;
            case 4: clearCars(); break;
            case 5: findCarByNumber(); break;
            case 6: searchCarsByBrand(); break;
            case 0: running = false; break;
            default: std::cout << "Некорректный пункт меню." << std::endl; waitEnter(); break;
        }
    }
}

void ConsoleUI::rentRepairMenu() {
    bool running = true;
    while (running) {
        printLine();
        std::cout << "Прокат и ремонт" << std::endl;
        std::cout << "1 - Отправить автомобиль в ремонт" << std::endl;
        std::cout << "2 - Зарегистрировать прибытие из ремонта" << std::endl;
        std::cout << "3 - Выдать автомобиль клиенту" << std::endl;
        std::cout << "4 - Принять автомобиль от клиента" << std::endl;
        std::cout << "5 - Просмотр активных записей проката" << std::endl;
        std::cout << "0 - Назад" << std::endl;
        int choice = readInt("Выбор: ");
        switch (choice) {
            case 1: sendCarToRepair(); break;
            case 2: receiveCarFromRepair(); break;
            case 3: rentCar(); break;
            case 4: returnCar(); break;
            case 5: listRentals(); break;
            case 0: running = false; break;
            default: std::cout << "Некорректный пункт меню." << std::endl; waitEnter(); break;
        }
    }
}

void ConsoleUI::structuresMenu() {
    bool running = true;
    while (running) {
        printLine();
        std::cout << "Служебный просмотр структур" << std::endl;
        std::cout << "1 - АВЛ-дерево клиентов" << std::endl;
        std::cout << "2 - Хеш-таблица автомобилей" << std::endl;
        std::cout << "3 - Циклический двунаправленный список проката" << std::endl;
        std::cout << "0 - Назад" << std::endl;
        int choice = readInt("Выбор: ");
        switch (choice) {
            case 1: service.printClientTree(); waitEnter(); break;
            case 2: service.printCarHashTable(); waitEnter(); break;
            case 3: service.printRentalList(); waitEnter(); break;
            case 0: running = false; break;
            default: std::cout << "Некорректный пункт меню." << std::endl; waitEnter(); break;
        }
    }
}

void ConsoleUI::registerClient() {
    printLine();
    std::string license = readLicense();
    std::string fullName = readLine("ФИО: ");
    std::string passport = readLine("Паспортные данные: ");
    std::string address = readLine("Адрес: ");
    std::string error;
    if (!validateNotEmpty(fullName, "ФИО", error) || !validateNotEmpty(passport, "Паспорт", error) || !validateNotEmpty(address, "Адрес", error)) {
        std::cout << "Ошибка: " << error << std::endl;
    } else {
        printResult(service.registerClient(Client(license, fullName, passport, address)));
    }
    waitEnter();
}

void ConsoleUI::removeClient() {
    printLine();
    std::string license = readLicense();
    printResult(service.removeClient(license));
    waitEnter();
}

void ConsoleUI::listClients() {
    printLine();
    auto items = service.listClients();
    if (items.empty()) std::cout << "Клиенты отсутствуют." << std::endl;
    for (const Client& client : items) {
        std::cout << "- " << client.getLicenseNumber() << ", " << client.getFullName() << ", " << client.getAddress() << std::endl;
    }
    waitEnter();
}

void ConsoleUI::clearClients() {
    printLine();
    std::cout << "Очистить всех клиентов? 1 - да, 0 - нет" << std::endl;
    if (readInt("Выбор: ") == 1) printResult(service.clearClients());
    waitEnter();
}

void ConsoleUI::findClientByLicense() {
    printLine();
    std::string license = readLicense();
    const Client* client = service.findClient(license);
    if (!client) {
        std::cout << "Клиент не найден." << std::endl;
    } else {
        printClient(*client);
        auto records = service.rentalsByClient(license);
        std::cout << "Выданные автомобили:" << std::endl;
        if (records.empty()) std::cout << "нет" << std::endl;
        for (const RentalRecord& record : records) std::cout << "- " << record.getCarNumber() << std::endl;
    }
    waitEnter();
}

void ConsoleUI::searchClientsByFragment() {
    printLine();
    std::string fragment = readLine("Фрагмент ФИО или адреса: ");
    auto items = service.searchClientsByFragment(fragment);
    if (items.empty()) std::cout << "Совпадения не найдены." << std::endl;
    for (const Client& client : items) {
        std::cout << "- " << client.getLicenseNumber() << ", " << client.getFullName() << ", " << client.getAddress() << std::endl;
    }
    waitEnter();
}

void ConsoleUI::addCar() {
    printLine();
    std::string number = readCarNumber();
    std::string brand = readLine("Марка: ");
    std::string color = readLine("Цвет: ");
    int year = readInt("Год выпуска: ");
    std::string error;
    if (!validateNotEmpty(brand, "Марка", error) || !validateNotEmpty(color, "Цвет", error) || !validateYear(year, error)) {
        std::cout << "Ошибка: " << error << std::endl;
    } else {
        printResult(service.addCar(Car(number, brand, color, year, true)));
    }
    waitEnter();
}

void ConsoleUI::removeCar() {
    printLine();
    std::string number = readCarNumber();
    printResult(service.removeCar(number));
    waitEnter();
}

void ConsoleUI::listCars() {
    printLine();
    auto items = service.listCars();
    if (items.empty()) std::cout << "Автомобили отсутствуют." << std::endl;
    for (const Car& car : items) {
        std::cout << "- " << car.getNumber() << ", " << car.getBrand() << ", " << car.getColor()
                  << ", " << car.getYear() << ", наличие: " << (car.isAvailable() ? "да" : "нет") << std::endl;
    }
    waitEnter();
}

void ConsoleUI::clearCars() {
    printLine();
    std::cout << "Очистить все автомобили? 1 - да, 0 - нет" << std::endl;
    if (readInt("Выбор: ") == 1) printResult(service.clearCars());
    waitEnter();
}

void ConsoleUI::findCarByNumber() {
    printLine();
    std::string number = readCarNumber();
    const Car* car = service.findCar(number);
    if (!car) {
        std::cout << "Автомобиль не найден." << std::endl;
    } else {
        printCar(*car);
        const RentalRecord* record = service.rentalByCar(number);
        if (record) {
            const Client* client = service.findClient(record->getClientLicenseNumber());
            std::cout << "Выдан клиенту: "
                      << (client ? client->getFullName() : "неизвестный клиент")
                      << ", ВУ: " << record->getClientLicenseNumber() << std::endl;
        } else {
            std::cout << "Клиенту не выдан." << std::endl;
        }
    }
    waitEnter();
}

void ConsoleUI::searchCarsByBrand() {
    printLine();
    std::string fragment = readLine("Фрагмент марки: ");
    auto items = service.searchCarsByBrand(fragment);
    if (items.empty()) std::cout << "Совпадения не найдены." << std::endl;
    for (const Car& car : items) {
        std::cout << "- " << car.getNumber() << ", " << car.getBrand() << ", " << car.getColor() << ", " << car.getYear() << std::endl;
    }
    waitEnter();
}

void ConsoleUI::sendCarToRepair() {
    printLine();
    std::string number = readCarNumber();
    printResult(service.sendCarToRepair(number));
    waitEnter();
}

void ConsoleUI::receiveCarFromRepair() {
    printLine();
    std::string number = readCarNumber();
    printResult(service.receiveCarFromRepair(number));
    waitEnter();
}

void ConsoleUI::rentCar() {
    printLine();
    std::string license = readLicense();
    std::string carNumber = readCarNumber();
    std::string issueDate = readLine("Дата выдачи: ");
    std::string returnDate = readLine("Дата возврата: ");
    std::string error;
    if (!validateNotEmpty(issueDate, "Дата выдачи", error) || !validateNotEmpty(returnDate, "Дата возврата", error)) {
        std::cout << "Ошибка: " << error << std::endl;
    } else {
        printResult(service.rentCar(license, carNumber, issueDate, returnDate));
    }
    waitEnter();
}

void ConsoleUI::returnCar() {
    printLine();
    std::string license = readLicense();
    std::string carNumber = readCarNumber();
    printResult(service.returnCar(license, carNumber));
    waitEnter();
}

void ConsoleUI::listRentals() {
    printLine();
    auto items = service.listRentals();
    if (items.empty()) std::cout << "Активные записи проката отсутствуют." << std::endl;
    for (const RentalRecord& record : items) printRental(record);
    waitEnter();
}
