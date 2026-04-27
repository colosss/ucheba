#include "calcfactory.h"

#include "abscalc.h"
#include "nyloncalc.h"
#include "placalc.h"
#include "resincalc.h"

std::unique_ptr<AbstractCalc> CalcFactory::createCalc(PrintJob::MaterialType type)
{
    switch (type) {
    case PrintJob::PLA:
        return std::make_unique<PLACalc>();
    case PrintJob::ABS:
        return std::make_unique<ABScalc>();
    case PrintJob::RESIN:
        return std::make_unique<resincalc>();
    case PrintJob::NYLON:
        return std::make_unique<nyloncalc>();
    default:
        return nullptr;
    }
}
