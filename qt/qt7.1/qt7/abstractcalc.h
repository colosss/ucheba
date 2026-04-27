#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "printjob.h"

class AbstractCalc
{
public:
    virtual ~AbstractCalc() = default;
    virtual int getCost(PrintJob *job) = 0;
};

#endif
