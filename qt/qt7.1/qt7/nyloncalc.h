#ifndef NYLONCALC_H
#define NYLONCALC_H

#include "abstractcalc.h"

class nyloncalc : public AbstractCalc
{
public:
    int getCost(PrintJob *job) override;
};

#endif
