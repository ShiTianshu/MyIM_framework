#ifndef IACT_H
#define IACT_H

#include "imod.h"

// 行为接口
class IAct:
        public IMod
{
public:
    IAct(QString id);
    virtual ~IAct() = 0;
    virtual void execute() = 0;
};

#endif // IACT_H
