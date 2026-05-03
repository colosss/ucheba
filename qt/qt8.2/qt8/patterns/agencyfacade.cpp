#include "agencyfacade.h"
#include "propertyfactory.h"

#include <QDate>

void AgencyFacade::addObserver(AgencyObserver *observer)
{
    if (!m_observers.contains(observer)) {
        m_observers.append(observer);
    }
}

void AgencyFacade::removeObserver(AgencyObserver *observer)
{
    m_observers.removeAll(observer);
}

const QVector<Property> &AgencyFacade::properties() const
{
    return m_properties;
}

const QVector<Client> &AgencyFacade::clients() const
{
    return m_clients;
}

const QVector<Deal> &AgencyFacade::deals() const
{
    return m_deals;
}

bool AgencyFacade::addProperty(const Property &property, QString &error)
{
    if (property.id() <= 0) {
        error = "Код объекта должен быть положительным";
        return false;
    }
    if (property.address().trimmed().isEmpty()) {
        error = "Введите адрес объекта";
        return false;
    }
    if (propertyIndexById(property.id()) != -1) {
        error = "Объект с таким кодом уже есть";
        return false;
    }
    m_properties.append(property);
    notifyObservers();
    return true;
}

bool AgencyFacade::addClient(const Client &client, QString &error)
{
    if (client.id() <= 0) {
        error = "Код клиента должен быть положительным";
        return false;
    }
    if (client.fullName().trimmed().isEmpty()) {
        error = "Введите ФИО клиента";
        return false;
    }
    if (client.phone().trimmed().isEmpty()) {
        error = "Введите телефон клиента";
        return false;
    }
    if (clientIndexById(client.id()) != -1) {
        error = "Клиент с таким кодом уже есть";
        return false;
    }
    m_clients.append(client);
    notifyObservers();
    return true;
}

bool AgencyFacade::addDeal(const Deal &deal, QString &error)
{
    int clientIndex = clientIndexById(deal.clientId());
    int propertyIndex = propertyIndexById(deal.propertyId());
    if (deal.id() <= 0) {
        error = "Код сделки должен быть положительным";
        return false;
    }
    if (dealIndexById(deal.id()) != -1) {
        error = "Сделка с таким кодом уже есть";
        return false;
    }
    if (clientIndex == -1) {
        error = "Выберите существующего клиента";
        return false;
    }
    if (propertyIndex == -1) {
        error = "Выберите существующий объект недвижимости";
        return false;
    }
    const Property &property = m_properties[propertyIndex];
    if (property.status() == "Продан" || property.status() == "Сдан") {
        error = "По выбранному объекту уже завершена сделка";
        return false;
    }
    if (deal.amount() <= 0) {
        error = "Сумма сделки должна быть положительной";
        return false;
    }
    m_deals.append(deal);
    refreshPropertyStatus(deal.propertyId());
    notifyObservers();
    return true;
}

bool AgencyFacade::removeProperty(int id, QString &error)
{
    int index = propertyIndexById(id);
    if (index == -1) {
        error = "Выберите объект для удаления";
        return false;
    }
    for (const Deal &deal : m_deals) {
        if (deal.propertyId() == id) {
            error = "Нельзя удалить объект, который участвует в сделках";
            return false;
        }
    }
    m_properties.removeAt(index);
    notifyObservers();
    return true;
}

bool AgencyFacade::removeClient(int id, QString &error)
{
    int index = clientIndexById(id);
    if (index == -1) {
        error = "Выберите клиента для удаления";
        return false;
    }
    for (const Deal &deal : m_deals) {
        if (deal.clientId() == id) {
            error = "Нельзя удалить клиента, который участвует в сделках";
            return false;
        }
    }
    m_clients.removeAt(index);
    notifyObservers();
    return true;
}

bool AgencyFacade::removeDeal(int id, QString &error)
{
    int index = dealIndexById(id);
    if (index == -1) {
        error = "Выберите сделку для удаления";
        return false;
    }
    int propertyId = m_deals[index].propertyId();
    m_deals.removeAt(index);
    refreshPropertyStatus(propertyId);
    notifyObservers();
    return true;
}

void AgencyFacade::clear()
{
    m_properties.clear();
    m_clients.clear();
    m_deals.clear();
    notifyObservers();
}

void AgencyFacade::seed()
{
    m_properties.clear();
    m_clients.clear();
    m_deals.clear();

    m_properties.append(PropertyFactory::create(101, "Квартира", "Невский проспект, 12", 2, 58.4, 7400000));
    m_properties.append(PropertyFactory::create(102, "Дом", "Солнечная улица, 8", 5, 146.0, 12800000));
    m_properties.append(PropertyFactory::create(103, "Коммерческое помещение", "Лиговский проспект, 50", 1, 82.5, 9600000));
    m_properties.append(PropertyFactory::create(104, "Квартира", "Московский проспект, 144", 3, 76.2, 8900000));
    m_properties.append(PropertyFactory::create(105, "Участок", "пос. Зеленый бор, участок 17", 0, 900.0, 3100000));

    m_clients.append(Client(201, "Иванов Илья Сергеевич", "+7-921-100-01-01", "Квартира", 9000000));
    m_clients.append(Client(202, "Петрова Анна Олеговна", "+7-911-105-23-35", "Дом", 15000000));
    m_clients.append(Client(203, "Сидоров Максим Павлович", "+7-911-107-07-07", "Коммерческое помещение", 10000000));
    m_clients.append(Client(204, "Кузнецова Мария Игоревна", "+7-981-222-32-11", "Участок", 3500000));

    m_deals.append(Deal(301, 201, 101, "Бронь", QDate::currentDate().addDays(-3).toString("dd.MM.yyyy"), 7400000, "Оформлена"));
    m_deals.append(Deal(302, 203, 103, "Аренда", QDate::currentDate().addDays(-1).toString("dd.MM.yyyy"), 85000, "Выполнена"));

    refreshPropertyStatus(101);
    refreshPropertyStatus(103);
    notifyObservers();
}

QVector<Property> AgencyFacade::availablePropertiesForClient(int clientId) const
{
    QVector<Property> result;
    int index = clientIndexById(clientId);
    if (index == -1) {
        return result;
    }
    const Client &client = m_clients[index];
    for (const Property &property : m_properties) {
        bool statusOk = property.status() == "Свободен" || property.status() == "Забронирован";
        bool typeOk = property.type() == client.needType();
        bool budgetOk = property.price() <= client.maxBudget();
        if (statusOk && typeOk && budgetOk) {
            result.append(property);
        }
    }
    return result;
}

QVector<Deal> AgencyFacade::dealsByClient(int clientId) const
{
    QVector<Deal> result;
    for (const Deal &deal : m_deals) {
        if (deal.clientId() == clientId) {
            result.append(deal);
        }
    }
    return result;
}

QVector<Deal> AgencyFacade::dealsByProperty(int propertyId) const
{
    QVector<Deal> result;
    for (const Deal &deal : m_deals) {
        if (deal.propertyId() == propertyId) {
            result.append(deal);
        }
    }
    return result;
}

int AgencyFacade::totalRevenue() const
{
    int sum = 0;
    for (const Deal &deal : m_deals) {
        if (deal.status() != "Отменена") {
            sum += deal.amount();
        }
    }
    return sum;
}

int AgencyFacade::propertyIndexById(int id) const
{
    for (int i = 0; i < m_properties.size(); ++i) {
        if (m_properties[i].id() == id) {
            return i;
        }
    }
    return -1;
}

int AgencyFacade::clientIndexById(int id) const
{
    for (int i = 0; i < m_clients.size(); ++i) {
        if (m_clients[i].id() == id) {
            return i;
        }
    }
    return -1;
}

int AgencyFacade::dealIndexById(int id) const
{
    for (int i = 0; i < m_deals.size(); ++i) {
        if (m_deals[i].id() == id) {
            return i;
        }
    }
    return -1;
}

void AgencyFacade::notifyObservers()
{
    for (AgencyObserver *observer : m_observers) {
        if (observer != nullptr) {
            observer->agencyChanged();
        }
    }
}

void AgencyFacade::refreshPropertyStatus(int propertyId)
{
    int propertyIndex = propertyIndexById(propertyId);
    if (propertyIndex == -1) {
        return;
    }
    QString status = "Свободен";
    for (const Deal &deal : m_deals) {
        if (deal.propertyId() != propertyId || deal.status() == "Отменена") {
            continue;
        }
        if (deal.operation() == "Продажа" && deal.status() == "Выполнена") {
            status = "Продан";
        } else if (deal.operation() == "Аренда" && deal.status() == "Выполнена") {
            status = "Сдан";
        } else if (deal.operation() == "Бронь") {
            status = "Забронирован";
        }
    }
    m_properties[propertyIndex].setStatus(status);
}
