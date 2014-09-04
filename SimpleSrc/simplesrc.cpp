#include "simplesrc.h"
#include "../MyBase/global.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTextCodec>
#include <QRegExp>


bool SrcLessThan(const Global::SrcItem &item1, const Global::SrcItem &item2)
{
    return item1.key < item2.key;
}

SimpleSrc* GetInstance()
{
    return new SimpleSrc;
}

SimpleSrc::SimpleSrc():
    ISrc()
{
    this->name = "SimpleSrc";
    this->cursor.setSrcs(&(this->words));
    this->cursor.setPageSize(5);
}

SimpleSrc::~SimpleSrc()
{

}

void SimpleSrc::initialize(const QMap<QString, QVariant> &envs)
{
    // file属性为码表名称。
    this->fileName = this->getIdConfig(envs, "file").toString();
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
    qDebug() << this->words;
    qDebug() << this->indexs;
}

//+-----------------------------------------------------------------------------
//
// 按行读取文件
//
//------------------------------------------------------------------------------

void SimpleSrc::_loadTxtFile(QFile *pf)
{
    QTextStream stream(pf);
    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        line.replace(QRegExp("[\\n|\\r]"), "");
        QStringList kv = line.split("\t");
        if (kv.length() < 2)
        {
            continue;
        }
        //Global::SrcEle src;
        Global::SrcItem item;
        item.key = kv.at(1);
        item.value = kv.at(0);
        this->words.append(item);
    }
    qStableSort(this->words.begin(), this->words.end(), SrcLessThan);
    this->_createIndexs();
}

void SimpleSrc::_loadBinFile(QFile *pf)
{
    QDataStream stream(pf);
    stream >> this->words;
    stream >> this->indexs;
}

void SimpleSrc::_createBinFile(QFile *pf)
{
    QDataStream stream(pf);
    stream << this->words;
    stream << this->indexs;
}

void SimpleSrc::_createIndexs()
{
    this->indexs.clear();
    uint index = 0;
    for (QVector< Global::SrcItem >::iterator it = this->words.begin();
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

void SimpleSrc::find(QString key,  Global::SrcCursor **ppCursor)
{
    qDebug() << "find invoked";
    *ppCursor = &(this->cursor);
    QHash< QString, quint32 >::iterator it = this->indexs.find(key);
    if (it != this->indexs.end())
    {
        this->cursor.setKey(key);
        this->cursor.setIndex(it.value()/10000);
        qDebug() << "current find" << this->words.at(it.value()/10000);
    }
}

void SimpleSrc::remove(uint)
{

}

void SimpleSrc::insert(QString key, QString value, QVariant ext)
{
    Global::SrcItem item;
    item.key = key;
    item.value = value;
    item.ext = ext;
    this->words.append(item);
    qStableSort(this->words.begin(), this->words.end(), SrcLessThan);
    QFile binFile(QString("%1/data/%2.bin").arg(Global::GetMyPath()).arg(fileName));
    this->_createBinFile(&binFile);
    binFile.close();
}
