#include "myengine.h"
#include "../MyBase/global.h"
#include "../MyBase/iact.h"

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
        QMap< QString, IMod* >::Iterator it = this->mods.find(actionId);
        if (it != this->mods.end())
        {
            if (((IMod*)it.value())->getType() != ACT_MOD)
            {
                throw QString("%1不是有效的Act模块").arg(((IMod*)it.value())->getFullName());
            }
            ((IAct*)it.value())->execute();
        }
    }

}


void MyEngine::onKeyDown()
{
    QVector< IProc* >::iterator it;
    for (it = this->keyDownProcList.begin();
         it != this->keyDownProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void MyEngine::onKeyUp()
{
    QVector< IProc* >::iterator it;
    for (it = this->keyUpProcList.begin();
         it != this->keyUpProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void MyEngine::onFocusIn()
{
    QVector< IProc* >::iterator it;
    for (it = this->focusInProcList.begin();
         it != this->focusInProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void MyEngine::onFocusOut()
{
    QVector< IProc* >::iterator it;
    for (it = this->focusOutProcList.begin();
         it != this->focusOutProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void MyEngine::_addKeyDownProc(IProc* iproc)
{
    this->keyDownProcList.append(iproc);
}


void MyEngine::_addKeyUpProc(IProc* iproc)
{
    this->keyUpProcList.append(iproc);
}


void MyEngine::_addFocusInProc(IProc* iproc)
{
    this->focusInProcList.append(iproc);
}


void MyEngine::_addFocusOutProc(IProc* iproc)
{
    this->focusOutProcList.append(iproc);
}





