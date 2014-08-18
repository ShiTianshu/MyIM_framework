#ifndef ACTMANAGER_H
#define ACTMANAGER_H

#include "../MyBase/iact.h"

#include <QString>

class ActManager
{
public:
    ActManager();
    virtual ~ActManager();
    void addAction(IAct* pa);
protected:
    QMap< QString, IAct* > acts;

};

#endif // ACTMANAGER_H
