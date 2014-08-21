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
    virtual void registerCtx(ulong id);
    virtual void unregisterCtx(ulong id);
    virtual void setCurrCtx(ulong id);

    // 事件相关
    virtual void onKeyDown(char key);
    virtual void onKeyUp(char key);
    virtual void onFocusIn();
    virtual void onFocusOut();

private:
    QMap< QString, QVariant > envs;
    QMap< QString, MyEngine* > engines;
    QMap< ulong, InputContext* > ctxs;

    InputContext* currCtx;  // 当前使用的上下文
    MyEngine* currEngine;   // 当前使用的引擎

    virtual void _loadConfig();
    virtual IMod* _loadMod(const QString & modName, const QString & modId);
    virtual void _loadEngine(const QString &name, const QString &engine);
    virtual void _loadIncludeConfig(const QStringList & includeList);
};

typedef MyCore* (*GetCoreInstance) ();

extern "C" MYCORESHARED_EXPORT MyCore* GetInstance();

#endif // MYCORE_H
