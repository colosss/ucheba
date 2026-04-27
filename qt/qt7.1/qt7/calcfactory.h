#ifndef CALCFACTORY_H
#define CALCFACTORY_H

#include <memory>

#include "abstractcalc.h"
#include "printjob.h"

class CalcFactory
{
public:
    static std::unique_ptr<AbstractCalc> createCalc(PrintJob::MaterialType type);
};

#endif
