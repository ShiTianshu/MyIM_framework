#include "isrc.h"

ISrc::ISrc(QString id):
    IMod(id)
{
    this->type = SRC_MOD;
    this->name = "ISrc";
}
