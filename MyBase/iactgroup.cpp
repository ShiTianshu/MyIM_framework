#include "iactgroup.h"

IActGroup::IActGroup():
    IAct()
{
    this->type = ACT_MOD;
    this->name = "IActGroup";
}

IActGroup::~IActGroup()
{

}
