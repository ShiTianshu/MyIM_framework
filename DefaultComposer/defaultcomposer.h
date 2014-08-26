#ifndef DEFAULTCOMPOSER_H
#define DEFAULTCOMPOSER_H

#include "defaultcomposer_global.h"
#include "../MyBase/iproc.h"

class DEFAULTCOMPOSERSHARED_EXPORT DefaultComposer:
        public IProc
{

public:
    DefaultComposer(QString id);
    virtual ~DefaultComposer();
    virtual void execute(InputContext *pic);
    virtual void initialize(const QMap<QString, QVariant> &);
};

extern "C" DEFAULTCOMPOSERSHARED_EXPORT DefaultComposer *GetInstance(QString modId);

#endif // DEFAULTCOMPOSER_H
