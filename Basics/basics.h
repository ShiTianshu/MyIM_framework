#ifndef BASICS_H
#define BASICS_H

#include "basics_global.h"
#include "../MyBase/iactgroup.h"

class BASICSSHARED_EXPORT Basics:
        public IActGroup
{
    Q_OBJECT
public:
    Basics();
    virtual ~Basics();
    virtual void initialize(const QMap<QString, QVariant> &);
    virtual void executeGroup(QString arg, InputContext *pic);
    virtual void execute(InputContext *);
};

extern "C" BASICSSHARED_EXPORT Basics* GetInstance();

#endif // BASICS_H
