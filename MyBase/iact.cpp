#include "iact.h"
#include "global.h"

IAct::IAct(QString id):
    IMod(id)
{
    this->type = ACT_MOD;
    this->name = "IAct";
}
