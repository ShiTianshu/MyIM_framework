#ifndef IMOD_H
#define IMOD_H

#include <QString>
#include <QVariant>
#include <QMap>

#include "global.h"

/**
 * @brief The IMod class
 * 基本模块接口，不可直接继承使用。
 */
class IMod: public QObject
{
    Q_OBJECT
public:
    IMod();
    virtual ~IMod();
    virtual void initialize(const QMap< QString, QVariant > &) = 0;
    const QString &getId();
    const QString &getName();
    void SetId(QString id);
    QString getFullName();
    const char &getType();

    virtual QStringList getNeccessaryParams();
    virtual QStringList getOptionalParams();

private:
    QString id;
protected:
    QString name;
    char type;
    QVariant getIdConfig(const QMap< QString, QVariant > &envs, QString key);
    QVariant getNameConfig(const QMap< QString, QVariant > &envs, QString key);
signals:
    void callAction(QString actionId);
    void srcFind(QString srcId, QString key);
    void srcCursor(QString srcId, Global::SrcCursor **ppcur);
    void srcRemove(QString srcId, uint id);
    void srcInsert(QString srcId, QString key, QString value, QVariant ext);
};

typedef IMod* (*GetModInstance) ();

#endif // IMOD_H
