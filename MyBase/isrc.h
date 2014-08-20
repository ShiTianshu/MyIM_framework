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

    virtual void findOne(QString key, Global::SrcEle *pe) = 0;
    virtual void find(QString key, QVector< Global::SrcEle > *pev) = 0;
    virtual void remove(uint id) = 0;
    virtual void update(Global::SrcEle *pe) = 0;
    virtual void add(Global::SrcEle *pe) = 0;
};

#endif // ISRC_H
