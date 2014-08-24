#include "hook.h"
#include <QDebug>

HHOOK gHook;
HINSTANCE gInstance;

extern "C" LRESULT CALLBACK KbProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT pkdhs = (PKBDLLHOOKSTRUCT)lParam;
    qDebug() << QString("wparam:%7, nCode:%1, vkCode:%2, dwExtraInfo:%3, scanCode:%4, time:%5, flags:%6")
                .arg(nCode).arg(pkdhs->vkCode).arg(pkdhs->dwExtraInfo).arg(pkdhs->scanCode).arg(pkdhs->time).arg(pkdhs->flags).arg(wParam);
    qDebug() << GetKeyState(VK_CONTROL) << "  ctrl  " << GetKeyState(VK_LCONTROL);
    qDebug() << GetKeyState(VK_SHIFT) << "  shift  " << GetKeyState(VK_LSHIFT);




    return CallNextHookEx(gHook, nCode, wParam, lParam);
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
