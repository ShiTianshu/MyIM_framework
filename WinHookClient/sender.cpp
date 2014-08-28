#include "sender.h"

#include "windows.h"
#include <winable.h>

void SendUnicode(wchar_t data)
{
  INPUT input[2];
  memset(input, 0, 2 * sizeof(INPUT));

  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk = 0;
  input[0].ki.wScan = data;
  input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;

  input[1].type = INPUT_KEYBOARD;
  input[1].ki.wVk = 0;
  input[1].ki.wScan = data;
  input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;

  SendInput(2, input, sizeof(INPUT));
}


void SendString(QString str)
{
    wchar_t wcstr[1024];
    int len = str.toWCharArray(wcstr);
    wcstr[len] = 0;
    for (wchar_t *p = wcstr; p < wcstr + 1024; ++p)
    {
        if (*p == 0) break;
        SendUnicode(*p);
    }
}
