#ifndef PROCMANAGER_H
#define PROCMANAGER_H

#include <QVector>
#include "../MyBase/iproc.h"

// 处理器管理器。
class ProcManager
{
public:
    ProcManager();
    virtual ~ProcManager();
    void onKeyDown();
    void onKeyUp();
    void onFocusIn();
    void onFocusOut();

protected:
    void _addKeyDownProc(IProc* iproc);
    void _addKeyUpProc(IProc* iproc);
    void _addFocusInProc(IProc* iproc);
    void _addFocusOutProc(IProc* iproc);

private:
    QVector< IProc* > keyDownProcList;
    QVector< IProc* > keyUpProcList;
    QVector< IProc* > focusInProcList;
    QVector< IProc* > focusOutProcList;
};

#endif // PROCMANAGER_H
