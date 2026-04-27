#ifndef PRINTJOB_H
#define PRINTJOB_H

#include <QObject>

class PrintJob : public QObject
{
    Q_OBJECT
public:
    enum MaterialType {
        PLA,
        ABS,
        RESIN,
        NYLON
    };

    explicit PrintJob(QObject *parent = nullptr);
    PrintJob(QString owner, int volume, int copies, int qualityIndex, int materialIndex, QObject *parent = nullptr);

    MaterialType getType() const;
    QString getOwner() const;
    int getVolume() const;
    int getCopies() const;
    int getQualityIndex() const;

private:
    QString owner;
    int volume;
    int copies;
    int qualityIndex;
    MaterialType material;
};

#endif
