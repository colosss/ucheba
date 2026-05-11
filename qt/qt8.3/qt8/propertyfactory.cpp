#include "propertyfactory.h"

Property PropertyFactory::create(int id, const QString &type, const QString &address, int rooms, double area, int price)
{
    return Property(id, type, address, rooms, area, price, "Свободен");
}
