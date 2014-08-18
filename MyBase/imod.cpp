#include "imod.h"
#include "global.h"

IMod::IMod(QString id)
{
    this->type = UNKNOWN_MOD;
    this->id = id;
    this->name = "IMod";
}

const QString &IMod::getId()
{
    return this->id;
}

const QString &IMod::getName()
{
    return this->name;
}

QString IMod::getFullName()
{
    QString fullName = QString("%1@%2(%3)").arg(this->name).arg(this->id).arg(this->type);
    return fullName;
}

const char &IMod::getType()
{
    return this->type;
}

QStringList IMod::getNeccessaryParams()
{
    return QStringList();
}

QStringList IMod::getOptionalParams()
{
    return QStringList();
}

void IMod::initialize(const QMap<QString, QVariant> &)
{

}
