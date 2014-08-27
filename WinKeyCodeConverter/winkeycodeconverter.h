#ifndef WINKEYCODECONVERTER_H
#define WINKEYCODECONVERTER_H

#include "winkeycodeconverter_global.h"
#include "../MyBase/iproc.h"

// Convert Win VkCode to QtKey
class WINKEYCODECONVERTERSHARED_EXPORT WinKeyCodeConverter:
        public IProc
{
public:
    WinKeyCodeConverter();
    virtual ~WinKeyCodeConverter();
    virtual void execute(InputContext *pic);
    virtual void initialize(const QMap<QString, QVariant> &);
};

extern "C" WINKEYCODECONVERTERSHARED_EXPORT WinKeyCodeConverter* GetInstance();
#endif // WINKEYCODECONVERTER_H
