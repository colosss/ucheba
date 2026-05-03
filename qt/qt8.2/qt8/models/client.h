#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
    Client();
    Client(int id, const QString &fullName, const QString &phone, const QString &needType, int maxBudget);

    int id() const;
    QString fullName() const;
    QString phone() const;
    QString needType() const;
    int maxBudget() const;

private:
    int m_id;
    QString m_fullName;
    QString m_phone;
    QString m_needType;
    int m_maxBudget;
};

#endif
