#ifndef ISRC_H
#define ISRC_H

#include "imod.h"

/**
 * @brief The ISrc class
 * 输入法数据源接口
 * 输入法所有静态数据保存在数据源中，提供增删改查的方法。
 * 数据源操作数据时与输入法上下文无关。
 * 继承需要实现find, findOne, remove, insert, initialize
 * 在查找的时候，返回的是对象，可以直接修改。所以没有update方法。
 */
class ISrc:
        public IMod
{
public:
    ISrc();
    virtual ~ISrc();

    virtual void find(QString key, Global::SrcCursor **ppCursor) = 0;
    virtual void remove(uint id) = 0;
    virtual void insert(QString key, QString value, QVariant ext) = 0;
};

#endif // ISRC_H
