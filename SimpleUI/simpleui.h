#ifndef SIMPLEUI_H
#define SIMPLEUI_H

#include "simpleui_global.h"
#include "../MyBase/iproc.h"
#include "candidate.h"

#include <QWidget>

class SIMPLEUISHARED_EXPORT SimpleUI: public IProc
{

public:
    SimpleUI();
    virtual ~SimpleUI();
    virtual void initialize(const QMap<QString, QVariant> &envs);
    virtual void execute(InputContext *pic);
private:
    Candidate* pcand;
};

extern "C" SIMPLEUISHARED_EXPORT SimpleUI *GetInstance();

#endif // SIMPLEUI_H
