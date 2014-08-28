#ifndef CARET_H
#define CARET_H

#include <windows.h>

inline void FillPos(POINT &point)
{
    GUITHREADINFO pg;
    pg.cbSize=48;
    ::GetGUIThreadInfo(0,&pg);
    if (pg.hwndCaret)
    {
        point.x=pg.rcCaret.right;
        point.y=pg.rcCaret.bottom;
        ::ClientToScreen(pg.hwndCaret,&point);
    }
}

#endif // CARET_H
