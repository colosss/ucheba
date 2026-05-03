#include "client.h"

Client::Client()
    : m_id(0)
    , m_maxBudget(0)
{
}

Client::Client(int id, const QString &fullName, const QString &phone, const QString &needType, int maxBudget)
    : m_id(id)
    , m_fullName(fullName)
    , m_phone(phone)
    , m_needType(needType)
    , m_maxBudget(maxBudget)
{
}

int Client::id() const
{
    return m_id;
}

QString Client::fullName() const
{
    return m_fullName;
}

QString Client::phone() const
{
    return m_phone;
}

QString Client::needType() const
{
    return m_needType;
}

int Client::maxBudget() const
{
    return m_maxBudget;
}
