#include "hook.h"
#include "socket.h"
#include <QDebug>

HHOOK gHook;
HINSTANCE gInstance;

extern "C" LRESULT CALLBACK KbProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT pkdhs = (PKBDLLHOOKSTRUCT)lParam;
//    qDebug() << QString("wparam:%7, nCode:%1, vkCode:%2, dwExtraInfo:%3, scanCode:%4, time:%5, flags:%6")
//                .arg(nCode).arg(pkdhs->vkCode).arg(pkdhs->dwExtraInfo).arg(pkdhs->scanCode).arg(pkdhs->time).arg(pkdhs->flags).arg(wParam);
//    qDebug() << GetKeyState(VK_CONTROL) << "  ctrl  " << GetKeyState(VK_LCONTROL);
//    qDebug() << GetKeyState(VK_SHIFT) << "  shift  " << GetKeyState(VK_LSHIFT);

    if (pkdhs->flags & LLKHF_INJECTED)
    {
        // pass
        return CallNextHookEx(gHook, nCode, wParam, lParam);
    }

    uint flags = 0;
    if (GetKeyState(VK_LCONTROL) < 0)
    {
        flags |= LCONTROL_FLAG;
    }
    if (GetKeyState(VK_RCONTROL) < 0)
    {
        flags |= RCONTROL_FLAG;
    }
    if (GetKeyState(VK_LSHIFT) < 0)
    {
        flags |= LSHIFT_FLAG;
    }
    if (GetKeyState(VK_RSHIFT) < 0)
    {
        flags |= RSHIFT_FLAG;
    }
    if (GetKeyState(VK_LMENU) < 0)
    {
        flags |= LMENU_FLAG;
    }
    if (GetKeyState(VK_RMENU) < 0)
    {
        flags |= RMENU_FLAG;
    }
    if (GetKeyState(VK_LWIN) < 0)
    {
        flags |= LSPECIAL_FLAG;
    }
    if (GetKeyState(VK_RWIN) < 0)
    {
        flags |= RSPECIAL_FLAG;
    }

    bool accepted = false;
    if (pkdhs->flags & LLKHF_UP)
    {
        accepted = SendKeyUp(pkdhs->vkCode, flags);
    }
    else
    {
        accepted = SendKeyDown(pkdhs->vkCode, flags);
    }
    qDebug() << accepted;

    if (accepted)
    {
        return 1;
    }
    else
    {
        return CallNextHookEx(gHook, nCode, wParam, lParam);
    }
}

void HookKeyboard()
{
    gInstance = (HINSTANCE)GetModuleHandle(NULL);
    gHook = SetWindowsHookEx(WH_KEYBOARD_LL, KbProc, gInstance, 0);
}

void UnhookKeyboard()
{
    UnhookWindowsHookEx(gHook);
}
