#include "iproc.h"
#include "global.h"

IProc::IProc(QString id):
    IMod(id)
{
    this->type = PROC_MOD;
    this->name = "IProc";
}


