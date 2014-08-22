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
        qDebug() << "读取bin";
        // 读取bin文件
        binFile.open(QFile::ReadOnly);
        this->_loadBinFile(&binFile);
        binFile.close();
    }
    else
    {
        qDebug() << "读取txt";
        QFile txtFile(QString("%1/data/%2.txt").arg(Global::GetMyPath()).arg(fileName));
        if (!txtFile.exists())
        {
            throw QString("file:%1不存在。").arg(fileName);
        }
        // 读取txt文件
        txtFile.open(QFile::ReadOnly);
        this->_loadTxtFile(&txtFile);
        txtFile.close();
        // 创建bin文件
        binFile.open(QFile::WriteOnly);
        this->_createBinFile(&binFile);
        binFile.close();
    }

//    Global::SrcEle src;
//    this->findOne("IbW_", &src);
//    qDebug() << src.key << src.value << src.id;
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
    QHash< QString, quint32 >::iterator it = this->indexs.find(key);
    if (it != this->indexs.end())
    {
        quint32 idx = it.value() / 10000;
        for (quint32 i = 0; i < it.value() % 10000; ++it)
        {
            pev->append(this->words.at(idx + i));
        }
    }
}

void SimpleSrc::findOne(QString key, Global::SrcEle *pe)
{
    QHash< QString, quint32 >::iterator it = this->indexs.find(key);
    if (it != this->indexs.end())
    {
        uint idx = it.value() / 10000;
        *pe = this->words.at(idx);
    }
}

//+---------------------------------------------------------------------
//
// 加载txt文件
// 词条放入vector数组。索引使用hash
//
//----------------------------------------------------------------------

void SimpleSrc::_loadTxtFile(QFile *pf)
{
    QTextStream stream(pf);

    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        qDebug() << "line:" << line;
        QStringList kv = line.trimmed().split("\t");
        if (kv.length() != 2)
        {
            throw QString("无效的编码格式。");
        }
        Global::SrcEle src;
        src.key = kv.at(1);
        src.value = kv.at(0);
        this->words.append(src);
    }
    qStableSort(this->words.begin(), this->words.end(), Global::SrcLessThan);
    this->_createIndexs();
}

void SimpleSrc::_loadBinFile(QFile *pf)
{
    QDataStream stream(pf);
    stream >> this->words;
    stream >> this->indexs;
    qDebug() << this->words;
    qDebug() << this->indexs;
}

void SimpleSrc::_createBinFile(QFile *pf)
{
    QDataStream stream(pf);
    stream << this->words;
    stream << this->indexs;
}

void SimpleSrc::_createIndexs()
{
    uint index = 0;
    for (QVector< Global::SrcEle >::iterator it = this->words.begin();
         it != this->words.end(); ++it)
    {
        it->id = index ++;
        QHash< QString, quint32 >::iterator it2 = this->indexs.find(it->key);
        if (it2 == this->indexs.end())
        {
            this->indexs[it->key] = it->id * 10000 + 1;
        }
        else
        {
            this->indexs[it->key] = it2.value() + 1;
        }
    }
}
