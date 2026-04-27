#ifndef RESINCALC_H
#define RESINCALC_H

#include "abstractcalc.h"

class resincalc : public AbstractCalc
{
public:
    int getCost(PrintJob *job) override;
};

#endif
