#ifndef SIMPLESRC_H
#define SIMPLESRC_H

#include "simplesrc_global.h"
#include "../MyBase/isrc.h"
#include "simplesrccursor.h"
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

private:
    QVector< Global::SrcItem > words;    // 词条
    QHash < QString, quint32 > indexs;  // 索引 %10000为词条数，/10000为下标
    SimpleSrcCursor cursor;        // 保有一个指针。

private:
    virtual void _loadTxtFile(QFile *pf);
    virtual void _loadBinFile(QFile *pf);
    virtual void _createBinFile(QFile *pf);
    virtual void _createIndexs();

    QString fileName;

    // ISrc interface
public:
    virtual void find(QString key, Global::SrcCursor **ppCursor);
    virtual void remove(uint);
    virtual void insert(QString key, QString value, QVariant ext);
};

extern "C" SIMPLESRCSHARED_EXPORT SimpleSrc* GetInstance();

#endif // SIMPLESRC_H
