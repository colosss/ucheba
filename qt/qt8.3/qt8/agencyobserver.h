#ifndef AGENCYOBSERVER_H
#define AGENCYOBSERVER_H

class AgencyObserver
{
public:
    virtual ~AgencyObserver() = default;
    virtual void agencyChanged() = 0;
};

#endif
