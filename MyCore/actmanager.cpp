#include "actmanager.h"

ActManager::ActManager()
{
}

ActManager::~ActManager()
{

}

void ActManager::addAction(IAct *pa)
{
    this->acts[pa->getId()] = pa;
}


