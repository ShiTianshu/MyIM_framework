#include "procmanager.h"

ProcManager::ProcManager()
{

}


ProcManager::~ProcManager()
{
    this->focusInProcList.clear();
    this->focusOutProcList.clear();
    this->keyDownProcList.clear();
    this->keyUpProcList.clear();
}


void ProcManager::onKeyDown()
{
    QVector< IProc* >::iterator it;
    for (it = this->keyDownProcList.begin();
         it != this->keyDownProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void ProcManager::onKeyUp()
{
    QVector< IProc* >::iterator it;
    for (it = this->keyUpProcList.begin();
         it != this->keyUpProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void ProcManager::onFocusIn()
{
    QVector< IProc* >::iterator it;
    for (it = this->focusInProcList.begin();
         it != this->focusInProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void ProcManager::onFocusOut()
{
    QVector< IProc* >::iterator it;
    for (it = this->focusOutProcList.begin();
         it != this->focusOutProcList.end(); ++it)
    {
        ((IProc*)*it)->execute();
    }
}


void ProcManager::_addKeyDownProc(IProc* iproc)
{
    this->keyDownProcList.append(iproc);
}


void ProcManager::_addKeyUpProc(IProc* iproc)
{
    this->keyUpProcList.append(iproc);
}


void ProcManager::_addFocusInProc(IProc* iproc)
{
    this->focusInProcList.append(iproc);
}


void ProcManager::_addFocusOutProc(IProc* iproc)
{
    this->focusOutProcList.append(iproc);
}

