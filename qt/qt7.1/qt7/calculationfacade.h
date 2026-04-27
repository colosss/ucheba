#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H

#include "printjob.h"

class CalculationFacade
{
public:
    static int getCost(PrintJob *job);
};

#endif
