#include "calculationfacade.h"

#include "calcfactory.h"

int CalculationFacade::getCost(PrintJob *job)
{
    auto calc = CalcFactory::createCalc(job->getType());

    if (!calc) {
        return -1;
    }

    return calc->getCost(job);
}
