#ifndef DEFAULTCOMPOSER_H
#define DEFAULTCOMPOSER_H

#include "defaultcomposer_global.h"
#include "../MyBase/iproc.h"

class DEFAULTCOMPOSERSHARED_EXPORT DefaultComposer:
        public IProc
{

public:
    DefaultComposer();
    virtual ~DefaultComposer();
    virtual void execute(InputContext *pic);
    virtual void initialize(const QMap<QString, QVariant> &);
};

extern "C" DEFAULTCOMPOSERSHARED_EXPORT DefaultComposer *GetInstance();

#endif // DEFAULTCOMPOSER_H
