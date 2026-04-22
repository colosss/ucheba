#include "printjob.h"

PrintJob::PrintJob(QObject *parent) : QObject(parent) {}

PrintJob::PrintJob(QString owner, int volume, int copies, int qualityIndex, int materialIndex, QObject *parent)
    : QObject(parent)
{
    this->owner = owner;
    this->volume = volume;
    this->copies = copies;
    this->qualityIndex = qualityIndex;
    this->material = static_cast<MaterialType>(materialIndex);
}

PrintJob::MaterialType PrintJob::getType() const { return material; }
QString PrintJob::getOwner() const { return owner; }
int PrintJob::getVolume() const { return volume; }
int PrintJob::getCopies() const { return copies; }
int PrintJob::getQualityIndex() const { return qualityIndex; }
