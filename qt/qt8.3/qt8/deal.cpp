#include "deal.h"

Deal::Deal()
    : m_id(0)
    , m_clientId(0)
    , m_propertyId(0)
    , m_amount(0)
{
}

Deal::Deal(int id, int clientId, int propertyId, const QString &operation, const QString &date, int amount, const QString &status)
    : m_id(id)
    , m_clientId(clientId)
    , m_propertyId(propertyId)
    , m_operation(operation)
    , m_date(date)
    , m_amount(amount)
    , m_status(status)
{
}

int Deal::id() const
{
    return m_id;
}

int Deal::clientId() const
{
    return m_clientId;
}

int Deal::propertyId() const
{
    return m_propertyId;
}

QString Deal::operation() const
{
    return m_operation;
}

QString Deal::date() const
{
    return m_date;
}

int Deal::amount() const
{
    return m_amount;
}

QString Deal::status() const
{
    return m_status;
}

void Deal::setStatus(const QString &status)
{
    m_status = status;
}

void Deal::setAmount(int amount)
{
    m_amount = amount;
}
