#ifndef MYCORE_H
#define MYCORE_H

#include "mycore_global.h"
#include "../MyBase/imod.h"
#include "../MyBase/inputcontext.h"
#include "myengine.h"

// 输入法核心
class MYCORESHARED_EXPORT MyCore
{

public:
    MyCore();
    virtual ~MyCore();
    virtual void initialize();

    // 切换引擎相关
    virtual void setEngine(QString engineId);

    // 上下文相关
    virtual void registerCtx(qint64 id);
    virtual void unregisterCtx(qint64 id);
    virtual void setCurrCtx(qint64 id);

    // 事件相关
    virtual QString onKeyDown(uint key);
    virtual QString onKeyUp(uint key);
    virtual QString onFocusIn();
    virtual QString onFocusOut();

    // 当前的InputContext是变换的，用于将其动态的传给engine
    InputContext *getCurrCtx();

private:
    QMap< QString, QVariant > envs;
    QMap< QString, MyEngine* > engines;
    QMap< qint64, InputContext* > ctxs;

    InputContext* currCtx;  // 当前使用的上下文
    MyEngine* currEngine;   // 当前使用的引擎

    virtual void _loadConfig();
    virtual IMod* _loadMod(const QString & modName, const QString & modId);
    virtual void _loadEngine(const QString &name, const QString &engine);
    virtual void _loadIncludeConfig(const QStringList & includeList);

    void _initEngines();

};

typedef MyCore* (*GetCoreInstance) ();

extern "C" MYCORESHARED_EXPORT MyCore* GetInstance();

#endif // MYCORE_H
