#include "property.h"

Property::Property()
    : m_id(0)
    , m_rooms(0)
    , m_area(0.0)
    , m_price(0)
{
}

Property::Property(int id, const QString &type, const QString &address, int rooms, double area, int price, const QString &status)
    : m_id(id)
    , m_type(type)
    , m_address(address)
    , m_rooms(rooms)
    , m_area(area)
    , m_price(price)
    , m_status(status)
{
}

int Property::id() const
{
    return m_id;
}

QString Property::type() const
{
    return m_type;
}

QString Property::address() const
{
    return m_address;
}

int Property::rooms() const
{
    return m_rooms;
}

double Property::area() const
{
    return m_area;
}

int Property::price() const
{
    return m_price;
}

QString Property::status() const
{
    return m_status;
}

void Property::setStatus(const QString &status)
{
    m_status = status;
}
