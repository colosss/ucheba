#ifndef PLACALC_H
#define PLACALC_H

#include "abstractcalc.h"

class PLACalc : public AbstractCalc
{
public:
    int getCost(PrintJob *job) override;
};

#endif
