#ifndef STATES_H
#define STATES_H

#include <QObject>
#include <QList>
#include "printjob.h"

class states : public QObject
{
    Q_OBJECT
public:
    explicit states(QObject *parent = nullptr);
    ~states() override;
    void undo();
    bool hasStates();
    PrintJob *getActualData();
    void add(PrintJob *job);
private:
    QList<PrintJob *> array;
    PrintJob *actualData;


signals:
    void notifyObservers();

};

#endif
