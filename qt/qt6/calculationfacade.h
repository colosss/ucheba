#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H

#include "printjob.h"
#include "placalc.h"
#include "abscalc.h"
#include "resincalc.h"
#include "nyloncalc.h"

class CalculationFacade
{
public:
    static int getCost(PrintJob *job);
};

#endif
