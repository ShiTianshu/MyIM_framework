#ifndef SRCMANAGER_H
#define SRCMANAGER_H

#include <QMap>
#include "../MyBase/global.h"
#include "../MyBase/isrc.h"

class SrcManager
{

public:
    SrcManager();
    virtual ~SrcManager();

private:
    QMap< QString, ISrc* > srcs;

};

#endif // SRCMANAGER_H
