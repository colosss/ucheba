#ifndef AGENCYFACADE_H
#define AGENCYFACADE_H

#include "agencyobserver.h"
#include "client.h"
#include "deal.h"
#include "property.h"

#include <QString>
#include <QVector>

class AgencyFacade
{
public:
    void addObserver(AgencyObserver *observer);
    void removeObserver(AgencyObserver *observer);

    const QVector<Property> &properties() const;
    const QVector<Client> &clients() const;
    const QVector<Deal> &deals() const;

    bool addProperty(const Property &property, QString &error);
    bool addClient(const Client &client, QString &error);
    bool addDeal(const Deal &deal, QString &error);
    bool removeProperty(int id, QString &error);
    bool removeClient(int id, QString &error);
    bool removeDeal(int id, QString &error);
    bool completeDeal(int id, QString &error);
    bool cancelDeal(int id, QString &error);
    void clear();
    void seed();

    QVector<Property> availablePropertiesForClient(int clientId) const;
    QVector<Deal> dealsByClient(int clientId) const;
    QVector<Deal> dealsByProperty(int propertyId) const;
    int totalRevenue() const;
    int propertyPrice(int propertyId) const;

private:
    QVector<Property> m_properties;
    QVector<Client> m_clients;
    QVector<Deal> m_deals;
    QVector<AgencyObserver *> m_observers;

    int propertyIndexById(int id) const;
    int clientIndexById(int id) const;
    int dealIndexById(int id) const;
    void notifyObservers();
    void refreshPropertyStatus(int propertyId);
};

#endif
