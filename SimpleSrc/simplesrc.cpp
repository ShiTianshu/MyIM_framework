#include "simplesrc.h"
#include "../MyBase/global.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>

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

//+---------------------------------------------------------------------
//
// 初始化
// 首选查找有没有.bin文件，如果有.bin文件，直接加载。
// 如果没有.bin文件，继续查找同名的.txt文件，如果没有.txt文件，异常。
// 有.txt文件，则转化成.bin文件。
//
//----------------------------------------------------------------------

void SimpleSrc::initialize(const QMap<QString, QVariant> &envs)
{
    qDebug() << "SimpleSrc初始化";
    // file属性为码表名称。
    QString fileName = this->getIdConfig(envs, "file").toString();
    if (fileName.isEmpty())
    {
        throw QString("%1模块需要指定参数file").arg(this->getFullName());
    }
    QFile binFile(QString("%1/data/%2.bin").arg(Global::GetMyPath()).arg(fileName));
    if (binFile.exists())
    {
        // 读取bin文件

    }
    else
    {
        QFile txtFile(QString("%1/data/%2.txt").arg(Global::GetMyPath()).arg(fileName));
        if (!txtFile.exists())
        {
            throw QString("file:%1不存在。").arg(fileName);
        }
        // 读取txt文件

    }

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

void SimpleSrc::_loadTxtFile(QFile *txtFile)
{

}

void SimpleSrc::_loadBinFile(QFile *binFile)
{

}

void SimpleSrc::_createBinFile()
{

}
