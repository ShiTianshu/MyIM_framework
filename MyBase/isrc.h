#ifndef ISRC_H
#define ISRC_H

#include "imod.h"

/**
 * @brief The ISrc class
 * 输入法数据源接口
 * 输入法所有静态数据保存在数据源中，提供增删改查的方法。
 * 数据源操作数据时与输入法上下文无关。
 * 继承需要实现find, findOne, remove, update, add, initialize
 */
class ISrc:
        public IMod
{
public:
    ISrc(QString id);
    virtual ~ISrc();

    virtual void findOne(QString key, Global::SrcEle *pe) = 0;
    virtual void find(QString key, QVector< Global::SrcEle > *pev) = 0;
    virtual void remove(uint id) = 0;
    virtual void update(Global::SrcEle *pe) = 0;
    virtual void add(Global::SrcEle *pe) = 0;
};

#endif // ISRC_H
