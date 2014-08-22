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
    IMod(QString id);
    virtual ~IMod();
    virtual void initialize(const QMap< QString, QVariant > &) = 0;
    const QString &getId();
    const QString &getName();
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

    /**
     * @brief action        触发行为
     * @param actionId      行为模块Id
     */
    void action(QString actionId);

    /**
     * @brief findOne       从数据源中查找一个数据。
     * @param srcId         数据源Id
     * @param key           键
     * @param pe            返回结果指针
     */
    void findOne(QString srcId, QString key, Global::SrcEle *pe);

    /**
     * @brief find          从数据源中查找一组数据
     * @param srcId         数据源Id
     * @param key           键
     * @param pev           返回结果的vector指针
     */
    void find(QString srcId, QString key, QVector< Global::SrcEle > *pev);

    /**
     * @brief remove        从数据源删除数据
     * @param srcId         数据源Id
     * @param id            要删除项的Id
     */
    void remove(QString srcId, uint id);

    /**
     * @brief update        从数据源更新数据
     * @param srcId         数据源Id
     * @param pe            要更新的项
     */
    void update(QString srcId, Global::SrcEle *pe);

    /**
     * @brief add           向数据源插入数据
     * @param srcId         数据源Id
     * @param pe            要插入的项
     */
    void add(QString srcId, Global::SrcEle *pe);
};

typedef IMod* (*GetModInstance) (QString modId);

#endif // IMOD_H
