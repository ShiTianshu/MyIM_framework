#include "myengine.h"
#include "typeinfo"
#include "../MyBase/global.h"
#include "../MyBase/iactgroup.h"
#include "mycore.h"

#include <QDebug>

MyEngine::MyEngine(QString name, MyCore *pc)
{
    this->name = name;
    this->core = pc;
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
        connect(it.value(), SIGNAL(toAction(QString)),
                this, SLOT(action(QString)));

        connect(it.value(), SIGNAL(toFind(QString,QString,Global::SrcCursor**)),
                this, SLOT(find(QString,QString,Global::SrcCursor**)));

        connect(it.value(), SIGNAL(toInsert(QString,QString,QString,QVariant)),
                this, SLOT(insert(QString,QString,QString,QVariant)));

        connect(it.value(), SIGNAL(toRemove(QString,uint)),
                this, SLOT(remove(QString,uint)));
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

void MyEngine::addUiProcList(QStringList procList)
{
    foreach (QString k, procList)
    {
        if (k.isEmpty()) break;
        QMap< QString, IMod* >::iterator it = this->mods.find(k);
        if (it == this->mods.end())
        {
            throw QString("ui事件响应中调用的模块%1未定义").arg(k);
        }
        this->_addUiProc((IProc*)it.value());
    }
}

void MyEngine::action(QString actionId)
{
    InputContext* pic = this->core->getCurrCtx();

    if (actionId.contains("#"))
    {
        // action group调用
        QStringList tmp = actionId.split("#");
        IAct* pa = this->_getAct(tmp.at(0));
        if (IActGroup *pag = dynamic_cast< IActGroup* >(pa))
        {
            pag->executeGroup(tmp.at(1), pic);
        }
        else
        {
            throw QString("模块%1不是ActGroup").arg(pa->getFullName());
        }
    }
    else
    {
        // 独立的action 调用
        IAct* pa = this->_getAct(actionId);
        pa->execute(pic);
    }
}

void MyEngine::find(QString srcId, QString key, Global::SrcCursor **ppCursor)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->find(key, ppCursor);
}

void MyEngine::remove(QString srcId, uint id)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->remove(id);
}

void MyEngine::insert(QString srcId, QString key, QString value, QVariant ext)
{
    ISrc* ps = this->_getSrc(srcId);
    ps->insert(key, value, ext);
}


void MyEngine::onKeyDown(uint keycode, uint keyFlags, InputContext *pic)
{
    if (pic)
    {
        // 设置键值
        pic->keycode = keycode;
        pic->keyPress = true;
        pic->keyFlags = keyFlags;
        pic->resetResponse();
        // 调用链
        QVector< IProc* >::iterator it;
        for (it = this->keyDownProcList.begin();
             it != this->keyDownProcList.end(); ++it)
        {
            ((IProc*)*it)->execute(pic);
        }
    }
    this->_uiProcInvoke(pic);
}


void MyEngine::onKeyUp(uint keycode, uint keyFlags, InputContext *pic)
{
    if (pic)
    {
        // 设置键值
        pic->keycode = keycode;
        pic->keyPress = false;
        pic->keyFlags = keyFlags;
        pic->resetResponse();
        // 调用链
        QVector< IProc* >::iterator it;
        for (it = this->keyUpProcList.begin();
             it != this->keyUpProcList.end(); ++it)
        {
            ((IProc*)*it)->execute(pic);
        }
    }
    this->_uiProcInvoke(pic);
}


void MyEngine::onFocusIn(InputContext *pic)
{
    if (pic)
    {
        pic->resetResponse();
        QVector< IProc* >::iterator it;
        for (it = this->focusInProcList.begin();
             it != this->focusInProcList.end(); ++it)
        {
            ((IProc*)*it)->execute(pic);
        }
        this->_uiProcInvoke(pic);
    }
}


void MyEngine::onFocusOut(InputContext *pic)
{
    if (pic)
    {
        pic->resetResponse();
        QVector< IProc* >::iterator it;
        for (it = this->focusOutProcList.begin();
             it != this->focusOutProcList.end(); ++it)
        {
            ((IProc*)*it)->execute(pic);
        }
        this->_uiProcInvoke(pic);
    }
}

void MyEngine::onPosChange(int x, int y, InputContext *pic)
{
    if (pic)
    {
        pic->caretPos.setX(x);
        pic->caretPos.setY(y);
        pic->resetResponse();
        this->_uiProcInvoke(pic);
    }
}

void MyEngine::_uiProcInvoke(InputContext *pic)
{
    QVector< IProc* >::iterator it;
    for (it = this->uiProcList.begin();
         it != this->uiProcList.end(); ++it)
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

void MyEngine::_addUiProc(IProc *iproc)
{
    this->uiProcList.append(iproc);
}






