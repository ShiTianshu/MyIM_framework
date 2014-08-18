#ifndef ISRC_H
#define ISRC_H

#include "imod.h"

// 数据源接口
class ISrc:
        public IMod
{
public:
    ISrc(QString id);
    virtual ~ISrc() = 0;

};

#endif // ISRC_H
