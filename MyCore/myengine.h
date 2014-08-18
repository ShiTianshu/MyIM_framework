#ifndef MYENGINE_H
#define MYENGINE_H

#include <QString>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <QObject>

#include "procmanager.h"
#include "actmanager.h"
#include "srcmanager.h"

class MyEngine:
        public QObject,
        public ProcManager,
        public ActManager,
        public SrcManager
{

    Q_OBJECT
public:
    MyEngine(QString name);
    virtual ~MyEngine();
    const QString & getName();
    void initialize(const QMap< QString, QVariant > &envs);
    void addMod(IMod* pm);

    void addKeyDownProcList(QStringList procList);
    void addKeyUpProcList(QStringList procList);
    void addFocusInProcList(QStringList procList);
    void addFocusOutProcList(QStringList procList);
private:
    QString name;
    QMap< QString, IMod* > mods;

public slots:
    void toAction(QString actionId);
    void findOne(QString srcId, QString key, Global::SrcEle *pe);
    void find(QString srcId, QString key, QVector< Global::SrcEle > *pev);
    void remove(QString srcId, uint id);
    void update(QString srcId, Global::SrcEle *pe);
    void add(QString srcId, Global::SrcEle *pe);
};

#endif // MYENGINE_H
