#include "placalc.h"

int PLACalc::getCost(PrintJob *job)
{
    double quality[] = {1.0, 1.5, 2.0};
    return job->getVolume() * job->getCopies() * 2 * quality[job->getQualityIndex()];
}
