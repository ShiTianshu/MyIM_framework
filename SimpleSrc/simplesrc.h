#ifndef SIMPLESRC_H
#define SIMPLESRC_H

#include "simplesrc_global.h"
#include "../MyBase/isrc.h"

class SIMPLESRCSHARED_EXPORT SimpleSrc: public ISrc
{
public:
    SimpleSrc(QString id);
    virtual ~SimpleSrc();

    // Implements
    virtual void initialize(const QMap< QString, QVariant > &envs);
    virtual void add(Global::SrcEle *pe);
    virtual void remove(uint id);
    virtual void update(Global::SrcEle *pe);
    virtual void find(QString key, QVector<Global::SrcEle> *pev);
    virtual void findOne(QString key, Global::SrcEle *pe);
};

extern "C" SIMPLESRCSHARED_EXPORT SimpleSrc* GetInstance(QString modId);

#endif // SIMPLESRC_H
