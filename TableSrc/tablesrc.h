#ifndef TABLESRC_H
#define TABLESRC_H

#include "tablesrc_global.h"
#include "../MyBase/isrc.h"
#include "../MyBase/global.h"
#include "tablecursor.h"

#include <QFile>

class TABLESRCSHARED_EXPORT TableSrc:
        public ISrc
{

public:
    TableSrc();
    virtual ~TableSrc();
    // IMod interface
public:
    virtual void initialize(const QMap<QString, QVariant> &env);

    // ISrc interface
public:
    virtual void find(QString key);
    virtual void srcCursor(Global::SrcCursor **ppcurr);
    virtual void remove(uint);
    virtual void insert(QString, QString, QVariant);

private:
    QString fileName;
    QVector < Global::SrcItem > datas;
    TableCursor cursor;

    void _loadBinFile(QFile *pf);
    void _createBinFile(QFile *pf);
    void _loadTxtFile(QFile *pf);
    int _binSearch(QString key, bool ext);
};

extern "C" TABLESRCSHARED_EXPORT TableSrc* GetInstance();
#endif // TABLESRC_H
