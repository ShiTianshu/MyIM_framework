#ifndef IPROC_H
#define IPROC_H

#include "imod.h"

// 处理器接口
class IProc:
        public IMod
{
public:
    IProc(QString id);
    virtual ~IProc()=0;
    virtual void execute()=0;
};

#endif // IPROC_H
