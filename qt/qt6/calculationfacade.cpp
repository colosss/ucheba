#include "calculationfacade.h"

int CalculationFacade::getCost(PrintJob *job)
{
    switch (job->getType()) {
    case PrintJob::PLA:
        return PLACalc::getCost(job);
    case PrintJob::ABS:
        return ABScalc::getCost(job);
    case PrintJob::RESIN:
        return resincalc::getCost(job);
    case PrintJob::NYLON:
        return nyloncalc::getCost(job);
    default:
        return -1;
    }
}
