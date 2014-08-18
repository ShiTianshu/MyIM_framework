#include "myengine.h"
#include "../MyBase/global.h"

#include <QDebug>

MyEngine::MyEngine(QString name)
{
    this->name = name;
}


MyEngine::~MyEngine()
{
    // delete所有的模块
    for (QMap< QString, IMod* >::iterator it = this->mods.begin();
         it != this->mods.end(); ++it)
    {
        delete it.value();
    }
}


const QString & MyEngine::getName()
{
    return this->name;
}


void MyEngine::initialize(const QMap<QString, QVariant> &envs)
{
    for (QMap< QString, IMod* >::iterator it = this->mods.begin();
         it != this->mods.end(); ++it)
    {
        it.value()->initialize(envs);
    }
}


void MyEngine::addMod(IMod *pm)
{
    char type = pm->getType();
    switch (type)
    {
    case PROC_MOD:
        break;
    case SRC_MOD:
        break;
    case ACT_MOD:
        this->addAction((IAct*)pm);
        break;
    case EXT_MOD:
        break;
    default:
        throw QString("无效的模块%1").arg(pm->getFullName());
    }
    this->mods[pm->getId()] = pm;
}


void MyEngine::addKeyDownProcList(QStringList procList)
{
    foreach (QString k, procList)
    {
        if (k.isEmpty()) break;
        QMap< QString, IMod* >::iterator it = this->mods.find(k);
        if (it == this->mods.end())
        {
            throw QString("keydown事件响应中调用的模块%1未定义").arg(k);
        }
        this->_addKeyDownProc((IProc*)it.value());
    }
}


void MyEngine::addKeyUpProcList(QStringList procList)
{
    foreach (QString k, procList)
    {
        if (k.isEmpty()) break;
        QMap< QString, IMod* >::iterator it = this->mods.find(k);
        if (it == this->mods.end())
        {
            throw QString("keyup事件响应中调用的模块%1未定义").arg(k);
        }
        this->_addKeyUpProc((IProc*)it.value());
    }
}


void MyEngine::addFocusInProcList(QStringList procList)
{
    foreach (QString k, procList)
    {
        if (k.isEmpty()) break;
        QMap< QString, IMod* >::iterator it = this->mods.find(k);
        if (it == this->mods.end())
        {
            throw QString("focusin事件响应中调用的模块%1未定义").arg(k);
        }
        this->_addFocusInProc((IProc*)it.value());
    }
}


void MyEngine::addFocusOutProcList(QStringList procList)
{
    foreach (QString k, procList)
    {
        if (k.isEmpty()) break;
        QMap< QString, IMod* >::iterator it = this->mods.find(k);
        if (it == this->mods.end())
        {
            throw QString("focusout事件响应中调用的模块%1未定义").arg(k);
        }
        this->_addFocusOutProc((IProc*)it.value());
    }
}

void MyEngine::findOne(QString srcId, QString key, Global::SrcEle *pe)
{
}

void MyEngine::find(QString srcId, QString key, QVector<Global::SrcEle> *pev)
{
}

void MyEngine::remove(QString srcId, uint id)
{
}

void MyEngine::update(QString srcId, Global::SrcEle *pe)
{
}

void MyEngine::add(QString srcId, Global::SrcEle *pe)
{

}

void MyEngine::toAction(QString actionId)
{
    if (actionId.contains("#"))
    {
        // action group调用
    }
    else
    {
        // 独立的action 调用
        QMap< QString, IAct* >::Iterator it = this->acts.find(actionId);
        if (it != this->acts.end())
        {
            ((IAct*)it.value())->execute();
        }
    }

}





