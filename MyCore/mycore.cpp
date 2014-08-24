#include "mycore.h"

#include "../MyBase/global.h"

#include <QDebug>
#include <QTextCodec>
#include <QLibrary>

MyCore::MyCore()
{

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
    IMod* pm = gmi(modId);
    if (!pm)
    {
        throw QString("无法创建模块实例%1").arg(modPath);
    }
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

void MyCore::onKeyDown(char key)
{
    this->currEngine->onKeyDown(key, this->currCtx);
}

void MyCore::onKeyUp(char key)
{
    this->currEngine->onKeyUp(key, this->currCtx);
}

void MyCore::onFocusIn()
{
    this->currEngine->onFocusIn(this->currCtx);
}

void MyCore::onFocusOut()
{
    this->currEngine->onFocusOut(this->currCtx);
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
    cfg.endGroup();
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


