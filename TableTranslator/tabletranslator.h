#ifndef TABLETRANSLATOR_H
#define TABLETRANSLATOR_H

#include "tabletranslator_global.h"
#include "../MyBase/iproc.h"

class TABLETRANSLATORSHARED_EXPORT TableTranslator:
    public IProc
{
    Q_OBJECT
public:
    TableTranslator();
    virtual ~TableTranslator();
    virtual void execute(InputContext* pic);
    virtual void initialize(const QMap<QString, QVariant> &envs);
private:
    int maxCodeLen;
};

extern "C" TABLETRANSLATORSHARED_EXPORT TableTranslator* GetInstance();

#endif // TABLETRANSLATOR_H
