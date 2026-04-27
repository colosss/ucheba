#ifndef ABSCALC_H
#define ABSCALC_H

#include "abstractcalc.h"

class ABScalc : public AbstractCalc
{
public:
    int getCost(PrintJob *job) override;
};

#endif
