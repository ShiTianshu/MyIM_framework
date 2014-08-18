#ifndef MYCORE_H
#define MYCORE_H

#include "mycore_global.h"
#include "../MyBase/imod.h"
#include "myengine.h"

// 输入法核心
class MYCORESHARED_EXPORT MyCore
{

public:
    MyCore();
    virtual ~MyCore();
    virtual void initialize();
private:
    QMap< QString, QVariant > envs;
    QMap< QString, MyEngine* > engines;

    virtual void _loadConfig();
    virtual IMod* _loadMod(const QString & modName, const QString & modId);
    virtual void _loadEngine(const QString &name, const QString &engine);
    virtual void _loadIncludeConfig(const QStringList & includeList);
};

typedef MyCore* (*GetCoreInstance) ();

extern "C" MYCORESHARED_EXPORT MyCore* GetInstance();

#endif // MYCORE_H
