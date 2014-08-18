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
    return pm;
}

void MyCore::initialize()
{
    qDebug() << "核心初始化开始";
    this->_loadConfig();
    qDebug() << "核心初始化完成";
}

void MyCore::_loadConfig()
{
    QSettings basicCfg(QString("%1/conf/myim.ini").arg(Global::GetMyPath()), QSettings::IniFormat);
    Global::SetSettingsCodec(&basicCfg);
    // 加载额外的配置文件
    QStringList includeList = basicCfg.value("include").toStringList();
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
    qDebug() << this->envs;
    qDebug() << this->engines;
}

void MyCore::_loadEngine(const QString & name, const QString & engine)
{
    qDebug() << "engine:" << name << "@" << engine;
    QSettings cfg(QString("%1/engine/%2.ini").arg(Global::GetMyPath()).arg(engine), QSettings::IniFormat);
    Global::SetSettingsCodec(&cfg);
    qDebug() << cfg.allKeys();
    qDebug() << cfg.childGroups();
    MyEngine* pe = new MyEngine(name);
    this->engines[name] = pe;
    // 加载模块
    QStringList sections;
    sections.append("PROC");sections.append("ACT");sections.append("SRC");sections.append("EXT");
    foreach(QString sec, sections)
    {
        cfg.beginGroup(sec);
        foreach(QString k, cfg.allKeys())
        {
            qDebug() << k;
            if (k.contains("#"))
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
    // 加载事件回调处理器链
    cfg.beginGroup("EVENT");
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

