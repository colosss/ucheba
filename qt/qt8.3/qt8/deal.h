#ifndef DEAL_H
#define DEAL_H

#include <QString>

class Deal
{
public:
    Deal();
    Deal(int id, int clientId, int propertyId, const QString &operation, const QString &date, int amount, const QString &status);

    int id() const;
    int clientId() const;
    int propertyId() const;
    QString operation() const;
    QString date() const;
    int amount() const;
    QString status() const;

    void setStatus(const QString &status);
    void setAmount(int amount);

private:
    int m_id;
    int m_clientId;
    int m_propertyId;
    QString m_operation;
    QString m_date;
    int m_amount;
    QString m_status;
};

#endif
