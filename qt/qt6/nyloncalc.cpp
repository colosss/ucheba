#include "nyloncalc.h"

int nyloncalc::getCost(PrintJob *job)
{
    double quality[] = {1.0, 1.5, 2.0};
    return job->getVolume() * job->getCopies() * 4 * quality[job->getQualityIndex()];
}
