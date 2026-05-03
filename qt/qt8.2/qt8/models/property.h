#ifndef PROPERTY_H
#define PROPERTY_H

#include <QString>

class Property
{
public:
    Property();
    Property(int id, const QString &type, const QString &address, int rooms, double area, int price, const QString &status);

    int id() const;
    QString type() const;
    QString address() const;
    int rooms() const;
    double area() const;
    int price() const;
    QString status() const;

    void setStatus(const QString &status);

private:
    int m_id;
    QString m_type;
    QString m_address;
    int m_rooms;
    double m_area;
    int m_price;
    QString m_status;
};

#endif
