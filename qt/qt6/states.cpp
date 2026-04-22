#include "states.h"


states::states(QObject *parent)
    : QObject{parent}
{
    actualData=nullptr;
}

states::~states()
{
    if (actualData){
        delete actualData;
        actualData=nullptr;
    }
    qDeleteAll(array);
    array.clear();
}

void states::add(PrintJob *job)
{
    array.append(job);
}

bool states::hasStates(){return !array.isEmpty();}

void states::undo()
{
    if (array.isEmpty()){
        actualData=nullptr;
    } else {
        actualData = array.last();
        array.removeLast();
    }
    emit notifyObservers();
}

PrintJob *states::getActualData()
{
    return actualData;
}
