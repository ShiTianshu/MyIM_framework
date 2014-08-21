#ifndef MYENGINE_H
#define MYENGINE_H

#include <QString>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <QObject>

#include "../MyBase/iproc.h"
#include "../MyBase/isrc.h"
#include "../MyBase/iact.h"

class MyEngine:
        public QObject
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

    void onKeyDown(char key, InputContext* pic);
    void onKeyUp(char key, InputContext* pic);
    void onFocusIn(InputContext* pic);
    void onFocusOut(InputContext* pic);

private:
    QString name;
    QMap< QString, IMod* > mods;
    QVector< IProc* > keyDownProcList;
    QVector< IProc* > keyUpProcList;
    QVector< IProc* > focusInProcList;
    QVector< IProc* > focusOutProcList;

    // 获得模块
    ISrc *_getSrc(QString srcId);
    IAct *_getAct(QString actId);

    // 添加处理器
    void _addKeyDownProc(IProc* iproc);
    void _addKeyUpProc(IProc* iproc);
    void _addFocusInProc(IProc* iproc);
    void _addFocusOutProc(IProc* iproc);

public slots:
    void toAction(QString actionId, InputContext* pic);
    void findOne(QString srcId, QString key, Global::SrcEle *pe);
    void find(QString srcId, QString key, QVector< Global::SrcEle > *pev);
    void remove(QString srcId, uint id);
    void update(QString srcId, Global::SrcEle *pe);
    void add(QString srcId, Global::SrcEle *pe);
};

#endif // MYENGINE_H
