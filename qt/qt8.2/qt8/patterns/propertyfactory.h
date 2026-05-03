#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H

#include "../models/property.h"

class PropertyFactory
{
public:
    static Property create(int id, const QString &type, const QString &address, int rooms, double area, int price);
};

#endif
