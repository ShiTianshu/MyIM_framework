#include "iactgroup.h"

IActGroup::IActGroup(QString id):
    IAct(id)
{
    this->type = ACT_MOD;
    this->name = "IActGroup";
}

IActGroup::~IActGroup()
{

}
