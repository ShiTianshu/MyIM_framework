#include "mycore.h"

#include "../MyBase/global.h"

#include <QDebug>
#include <QTextCodec>
#include <QLibrary>

MyCore::MyCore()
{
    this->currCtx = 0;
    this->currEngine = 0;
}

MyCore::~MyCore()
{
    // delete 所有engine
    QMap< QString, MyEngine* >::iterator it;
    for (it = this->engines.begin(); it != this->engines.end(); ++it)
    {
        delete it.value();
    }
}

MyCore* GetInstance()
{
    return new MyCore();
}

IMod* MyCore::_loadMod(const QString &modName, const QString &modId)
{
    QString modPath = QString("%1/mod/%2").arg(Global::GetMyPath()).arg(modName);
    QLibrary modLib(modPath);
    if (!modLib.load())
    {
        throw QString("无法找到模块，路径%1").arg(modPath);
    }
    GetModInstance gmi = (GetModInstance)modLib.resolve("GetInstance");
    if (!gmi)
    {
        throw QString("模块%1缺少GetInstance函数").arg(modPath);
    }
    IMod* pm = gmi();
    if (!pm)
    {
        throw QString("无法创建模块实例%1").arg(modPath);
    }
    pm->SetId(modId);
    qDebug() << QString("成功加载模块%1").arg(pm->getFullName());
    return pm;
}

void MyCore::initialize()
{
    qDebug() << "核心初始化开始";
    this->_loadConfig();
    this->_initEngines();
    qDebug() << "核心初始化完成";
}

void MyCore::setEngine(QString engineId)
{
    // 切换引擎要清空所有的上下文
    for (QMap< qint64, InputContext* >::iterator it = this->ctxs.begin();
         it != this->ctxs.end(); ++it)
    {
        it.value()->resetAll();
    }
    // 切换引擎
    QMap< QString, MyEngine* >::iterator itm;
    itm = this->engines.find(engineId);
    if (itm == this->engines.end())
    {
        throw QString("切换%1无效").arg(engineId);
    }
    this->currEngine = itm.value();
}

void MyCore::registerCtx(qint64 id)
{
    qDebug() << QString("创建上下文%1").arg(id);
    InputContext* pic = new InputContext(id);
    this->ctxs[id] = pic;
    this->currCtx = pic;
}

void MyCore::unregisterCtx(qint64 id)
{
    qDebug() << QString("注销上下文%1").arg(id);
    QMap< qint64, InputContext* >::iterator it;
    it = this->ctxs.find(id);
    if (it == this->ctxs.end())
    {
        throw QString("注销无效的上下文。ID=%1").arg(id);
    }
    delete it.value();
    this->ctxs.remove(id);
    this->currCtx = 0;
}

void MyCore::setCurrCtx(qint64 id)
{
    qDebug() << QString("上下文从%1切换到%2").arg(this->currCtx->id).arg(id);
    QMap< qint64, InputContext* >::iterator it;
    it = this->ctxs.find(id);
    if (it == this->ctxs.end())
    {
        throw QString("使用无效的上下文。ID=%1").arg(id);
    }
    this->currCtx = it.value();
}

QString MyCore::onKeyDown(uint key, uint flags)
{
    if (!this->currCtx)
    {
        return "N";
    }
    else
    {
        this->currEngine->onKeyDown(key, flags, this->currCtx);
        qDebug() << "finish key down:" << this->currCtx->accepted;
        return Global::ResponseData(this->currCtx->accepted, this->currCtx->commitString, this->currCtx->editText);
    }
}

QString MyCore::onKeyUp(uint key, uint flags)
{
    if (!this->currCtx)
    {
        return "N";
    }
    else
    {
        this->currEngine->onKeyUp(key, flags, this->currCtx);
        qDebug() << "finish key up:" << this->currCtx->accepted;
        return Global::ResponseData(this->currCtx->accepted, this->currCtx->commitString, this->currCtx->editText);
    }
}

QString MyCore::onFocusIn()
{
    if (!this->currCtx)
    {
        return "N";
    }
    else
    {
        this->currEngine->onFocusIn(this->currCtx);
        return Global::ResponseData(this->currCtx->accepted, this->currCtx->commitString, this->currCtx->editText);
    }
}

QString MyCore::onFocusOut()
{
    if (!this->currCtx)
    {
        return "N";
    }
    else
    {
        this->currEngine->onFocusOut(this->currCtx);
        return Global::ResponseData(this->currCtx->accepted, this->currCtx->commitString, this->currCtx->editText);
    }
}

QString MyCore::onPosChange(int x, int y)
{
    if (!this->currCtx)
    {
        return "N";
    }
    else
    {
        this->currEngine->onPosChange(x, y, this->currCtx);
        return Global::ResponseData(this->currCtx->accepted, this->currCtx->commitString, this->currCtx->editText);
    }
}

InputContext *MyCore::getCurrCtx()
{
    return this->currCtx;
}

void MyCore::_loadConfig()
{
    qDebug() << "加载配置文件开始";
    QSettings basicCfg(QString("%1/conf/myim.ini").arg(Global::GetMyPath()), QSettings::IniFormat);
    Global::SetSettingsCodec(&basicCfg);
    // 加载额外的配置文件
    QStringList includeList = basicCfg.value("configs").toStringList();
    this->_loadIncludeConfig(includeList);
    // 加载引擎配置文件
    foreach (QString str, basicCfg.childGroups())
    {
        basicCfg.beginGroup(str);
        QString name = basicCfg.value("name").toString();
        QString engine = basicCfg.value("engine").toString();
        this->_loadEngine(name, engine);
        basicCfg.endGroup();
    }
    qDebug() << "加载配置文件完成";
}

void MyCore::_loadEngine(const QString & name, const QString & engine)
{
    qDebug() << "加载ENGINE:" << name << "@" << engine;
    QSettings cfg(QString("%1/engine/%2.ini").arg(Global::GetMyPath()).arg(engine), QSettings::IniFormat);
    Global::SetSettingsCodec(&cfg);
    MyEngine* pe = new MyEngine(name, this);
    this->engines[name] = pe;
    // 加载模块
    QStringList sections;
    sections.append("PROC");sections.append("ACT");sections.append("SRC");sections.append("EXT");
    foreach(QString sec, sections)
    {
        cfg.beginGroup(sec);
        foreach(QString k, cfg.allKeys())
        {
            if (k.contains("/"))
            {
                // 参数
                this->envs[k] = cfg.value(k);
            }
            else
            {
                // 模块
                IMod* pm = this->_loadMod(cfg.value(k).toString(), k);
                pe->addMod(pm);
            }
        }
        cfg.endGroup();
    }
    qDebug() << "加载事件回调链";
    // 加载事件回调处理器链
    cfg.beginGroup("ENGINE");
    pe->addKeyDownProcList(cfg.value("keydown").toStringList());
    pe->addKeyUpProcList(cfg.value("keyup").toStringList());
    pe->addFocusInProcList(cfg.value("focusin").toStringList());
    pe->addFocusOutProcList(cfg.value("focusout").toStringList());
    pe->addUiProcList(cfg.value("ui").toStringList());
    cfg.endGroup();
    // 如果没有currEngine则赋值
    if (!this->currEngine)
    {
        this->currEngine = pe;
    }
}

void MyCore::_loadIncludeConfig(const QStringList & includeList)
{
    foreach (QString str, includeList)
    {
        QSettings cfg(QString("%1/conf/%2.ini").arg(Global::GetMyPath()).arg(str), QSettings::IniFormat);
        Global::SetSettingsCodec(&cfg);
        foreach (QString k, cfg.allKeys())
        {
            this->envs[k] = cfg.value(k);
        }
    }
}

void MyCore::_initEngines()
{
    qDebug() << "初始化引擎开始";
    for (QMap< QString, MyEngine* >::iterator it = this->engines.begin();
         it != this->engines.end(); ++it)
    {
        it.value()->initialize(this->envs);
    }
    qDebug() << "初始化引擎完成";
}


