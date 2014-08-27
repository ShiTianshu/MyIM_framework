#ifndef SIMPLESRC_H
#define SIMPLESRC_H

#include "simplesrc_global.h"
#include "../MyBase/isrc.h"
#include <QFile>
#include <QHash>
#include <QVector>

class SIMPLESRCSHARED_EXPORT SimpleSrc: public ISrc
{
public:
    SimpleSrc();
    virtual ~SimpleSrc();

    // Implements
    virtual void initialize(const QMap< QString, QVariant > &envs);
    virtual void add(Global::SrcEle *);
    virtual void remove(uint);
    virtual void update(Global::SrcEle *);
    virtual void find(QString key, QVector<Global::SrcEle> *pev);
    virtual void findOne(QString key, Global::SrcEle *pe);

private:
    QVector< Global::SrcEle > words;    // 词条
    QHash < QString, quint32 > indexs;  // 索引 %10000为词条数，/10000为下标

private:
    virtual void _loadTxtFile(QFile *pf);
    virtual void _loadBinFile(QFile *pf);
    virtual void _createBinFile(QFile *pf);
    virtual void _createIndexs();
};

extern "C" SIMPLESRCSHARED_EXPORT SimpleSrc* GetInstance();

#endif // SIMPLESRC_H
