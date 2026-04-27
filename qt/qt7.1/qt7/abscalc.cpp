#include "abscalc.h"

int ABScalc::getCost(PrintJob *job)
{
    double quality[] = {1.0, 1.5, 2.0};
    return job->getVolume() * job->getCopies() * 2.25 * quality[job->getQualityIndex()];
}
