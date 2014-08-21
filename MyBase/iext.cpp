#include "iext.h"

#include "global.h"

IExt::IExt(QString id):
    IMod(id)
{
    this->type = EXT_MOD;
    this->name = "IExt";
}

IExt::~IExt()
{

}
