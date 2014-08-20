#ifndef IACTGROUP_H
#define IACTGROUP_H

#include "iact.h"

// 行为组接口。
class IActGroup: public IAct
{
public:
    IActGroup(QString id);
    virtual ~IActGroup() = 0;
    virtual void execute(QString arg) = 0;
};

#endif // IACTGROUP_H
