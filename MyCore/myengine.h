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

class MyCore;

class MyEngine:
        public QObject
{

    Q_OBJECT
public:
    MyEngine(QString name, MyCore *pc);
    virtual ~MyEngine();
    const QString & getName();
    void initialize(const QMap< QString, QVariant > &envs);
    void addMod(IMod* pm);

    void addKeyDownProcList(QStringList procList);
    void addKeyUpProcList(QStringList procList);
    void addFocusInProcList(QStringList procList);
    void addFocusOutProcList(QStringList procList);
    void addUiProcList(QStringList procList);

    void onKeyDown(uint keycode, uint keyFlags, InputContext* pic);
    void onKeyUp(uint keycode, uint keyFlags, InputContext* pic);
    void onFocusIn(InputContext* pic);
    void onFocusOut(InputContext* pic);
    void onPosChange(int x, int y, InputContext* pic);
    void _uiProcInvoke(InputContext *pic);

private:
    QString name;
    QMap< QString, IMod* > mods;
    QVector< IProc* > keyDownProcList;
    QVector< IProc* > keyUpProcList;
    QVector< IProc* > focusInProcList;
    QVector< IProc* > focusOutProcList;
    QVector< IProc* > uiProcList;

    // 核心实例，用于获取当前的上下文
    MyCore* core;

    // 获得模块
    ISrc *_getSrc(QString srcId);
    IAct *_getAct(QString actId);

    // 添加处理器
    void _addKeyDownProc(IProc* iproc);
    void _addKeyUpProc(IProc* iproc);
    void _addFocusInProc(IProc* iproc);
    void _addFocusOutProc(IProc* iproc);
    void _addUiProc(IProc* iproc);

public slots:
    void action(QString actionId);
    void find(QString srcId, QString key);
    void remove(QString srcId, uint id);
    void insert(QString srcId, QString key, QString value, QVariant ext);
    void srcCursor(QString srcId, Global::SrcCursor **ppCursor);
};

#endif // MYENGINE_H
