#include "imod.h"
#include "global.h"

IMod::IMod(QString id)
{
    this->type = UNKNOWN_MOD;
    this->id = id;
    this->name = "IMod";
}

IMod::~IMod()
{

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

QVariant IMod::getIdConfig(const QMap<QString, QVariant> &envs, QString key)
{
    QMap< QString, QVariant >::const_iterator it;
    it = envs.find(QString("%1/%2").arg(this->id).arg(key));
    if (it == envs.end())
    {
        return QVariant();
    }
    else
    {
        if (it.value().toString().startsWith("$"))
        {
            // 引入参数
            QString key = it.value().toString().remove(0, 1);
            it = envs.find(key);
            if (it == envs.end())
            {
                return key;
            }
            else
            {
                return it.value();
            }
        }
        return it.value();
    }
}

QVariant IMod::getNameConfig(const QMap<QString, QVariant> &envs, QString key)
{
    QMap< QString, QVariant >::const_iterator it;
    it = envs.find(QString("%1/%2").arg(this->name).arg(key));
    if (it == envs.end())
    {
        return QVariant();
    }
    else
    {
        if (it.value().toString().contains("$"))
        {
            // 引入参数
            QString key = it.value().toString().remove(0, 1);
            it = envs.find(key);
            if (it == envs.end())
            {
                return key;
            }
            else
            {
                return it.value();
            }
        }
        return it.value();
    }
}
