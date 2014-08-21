#include "myengine.h"
#include "typeinfo"
#include "../MyBase/global.h"
#include "../MyBase/iactgroup.h"

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
        // 模块初始化。
        qDebug() << QString("%1初始化").arg(it.value()->getFullName());
        it.value()->initialize(envs);
        qDebug() << QString("%1连接信号槽").arg(it.value()->getFullName());
        // 连接信号和槽
        connect(it.value(), SIGNAL(action(QString)),
                this, SLOT(toAction(QString)));

        connect(it.value(), SIGNAL(find(QString,QString,QVector<Global::SrcEle>*)),
                this, SLOT(find(QString,QString,QVector<Global::SrcEle>*)));

        connect(it.value(), SIGNAL(findOne(QString,QString,Global::SrcEle*)),
                this, SLOT(findOne(QString,QString,Global::SrcEle*)));

        connect(it.value(), SIGNAL(remove(QString,uint)),
                this, SLOT(remove(QString,uint)));

        connect(it.value(), SIGNAL(add(QString,Global::SrcEle*)),
                this, SLOT(add(QString,Global::SrcEle*)));

        connect(it.value(), SIGNAL(update(QString,Global::SrcEle*)),
                this, SLOT(update(QString,Global::SrcEle*)));
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
    ISrc* ps = this->_getSrc(srcId);
    ps->findOne(key, pe);
}

void MyEngine::find(QString srcId, QString key, QVector<Global::SrcEle> *pev)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->find(key, pev);
}

void MyEngine::remove(QString srcId, uint id)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->remove(id);
}

void MyEngine::update(QString srcId, Global::SrcEle *pe)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->update(pe);
}

void MyEngine::add(QString srcId, Global::SrcEle *pe)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->add(pe);
}

void MyEngine::toAction(QString actionId, InputContext* pic)
{
    if (actionId.contains("#"))
    {
        // action group调用
        QStringList tmp = actionId.split("#");
        IAct* pa = this->_getAct(tmp.at(0));
        if (typeid(pa) != typeid(IActGroup*))
        {
            throw QString("模块%1不是ActGroup").arg(pa->getFullName());
        }
        IActGroup* pag = (IActGroup*) pa;
        pag->executeGroup(tmp.at(1), pic);
    }
    else
    {
        // 独立的action 调用
        IAct* pa = this->_getAct(actionId);
        pa->execute(pic);
    }
}


void MyEngine::onKeyDown(char key, InputContext *pic)
{
    // 设置键值
    pic->key = key;
    pic->keyPress = true;
    // 调用链
    QVector< IProc* >::iterator it;
    for (it = this->keyDownProcList.begin();
         it != this->keyDownProcList.end(); ++it)
    {
        ((IProc*)*it)->execute(pic);
    }
}


void MyEngine::onKeyUp(char key, InputContext *pic)
{
    // 设置键值
    pic->key = key;
    pic->keyPress = false;
    // 调用链
    QVector< IProc* >::iterator it;
    for (it = this->keyUpProcList.begin();
         it != this->keyUpProcList.end(); ++it)
    {
        ((IProc*)*it)->execute(pic);
    }
}


void MyEngine::onFocusIn(InputContext *pic)
{
    QVector< IProc* >::iterator it;
    for (it = this->focusInProcList.begin();
         it != this->focusInProcList.end(); ++it)
    {
        ((IProc*)*it)->execute(pic);
    }
}


void MyEngine::onFocusOut(InputContext *pic)
{
    QVector< IProc* >::iterator it;
    for (it = this->focusOutProcList.begin();
         it != this->focusOutProcList.end(); ++it)
    {
        ((IProc*)*it)->execute(pic);
    }
}

ISrc *MyEngine::_getSrc(QString srcId)
{
    QMap< QString, IMod* >::iterator it = this->mods.find(srcId);
    if (it == mods.end())
    {
        throw QString("必需的模块不存在：%1").arg(srcId);
    }
    else if (it.value()->getType() != SRC_MOD)
    {
        throw QString("调用的模块：%1不是Src模块").arg(it.value()->getFullName());
    }
    return ((ISrc*)it.value());
}

IAct *MyEngine::_getAct(QString actId)
{
    QMap< QString, IMod* >::iterator it = this->mods.find(actId);
    if (it == mods.end())
    {
        throw QString("必需的模块不存在：%1").arg(actId);
    }
    else if (it.value()->getType() != ACT_MOD)
    {
        throw QString("调用的模块：%1不是Act模块").arg(it.value()->getFullName());
    }
    return ((IAct*)it.value());
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





