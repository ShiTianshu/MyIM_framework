#ifndef CARET_H
#define CARET_H

#include <windows.h>
#include <QDebug>

inline void FillPos(POINT &point)
{
    GUITHREADINFO pg;
    pg.cbSize=48;
    ::GetGUIThreadInfo(0,&pg);
    if (pg.hwndCaret)
    {
        point.x=pg.rcCaret.right;
        point.y=pg.rcCaret.bottom;
    }
    else
    {
        point.x = 0;
        point.y = 0;
    }
    ::ClientToScreen(::GetForegroundWindow(),&point);
}

#endif // CARET_H
