#include "simplesrc.h"

#include <QDebug>

SimpleSrc* GetInstance(QString modId)
{
    return new SimpleSrc(modId);
}

SimpleSrc::SimpleSrc(QString id):
    ISrc(id)
{
    this->name = "SimpleSrc";
}

SimpleSrc::~SimpleSrc()
{

}

void SimpleSrc::initialize(const QMap<QString, QVariant> &envs)
{
    qDebug() << "SimpleSrc initialize...";
    qDebug() << envs;
    // file属性为码表名称。
    QString fileName = this->getIdConfig(envs, "file").toString();
    qDebug() << fileName;
}

void SimpleSrc::add(Global::SrcEle *pe)
{

}

void SimpleSrc::remove(uint id)
{

}

void SimpleSrc::update(Global::SrcEle *pe)
{

}

void SimpleSrc::find(QString key, QVector<Global::SrcEle> *pev)
{

}

void SimpleSrc::findOne(QString key, Global::SrcEle *pe)
{

}
