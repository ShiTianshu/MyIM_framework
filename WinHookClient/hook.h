#ifndef HOOK_H
#define HOOK_H

#include "windows.h"

extern "C" LRESULT CALLBACK KbProc(int nCode, WPARAM wParam, LPARAM lParam);
void HookKeyboard();
void UnhookKeyboard();

#endif // HOOK_H
