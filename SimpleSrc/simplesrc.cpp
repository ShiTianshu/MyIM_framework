#include "simplesrc.h"
#include "../MyBase/global.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTextCodec>


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
}

SimpleSrc::~SimpleSrc()
{

}

void SimpleSrc::initialize(const QMap<QString, QVariant> &envs)
{
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
    qDebug() << this->words;
    qDebug() << this->indexs;
}

void SimpleSrc::add(Global::SrcEle*)
{

}

void SimpleSrc::remove(uint)
{

}

void SimpleSrc::update(Global::SrcEle *)
{

}

void SimpleSrc::find(QString key, QVector<Global::SrcEle> *pev)
{
    // 检索精确对应的
    QHash< QString, quint32 >::iterator it = this->indexs.find(key);
    if (it != this->indexs.end())
    {
        quint32 idx = it.value() / 10000;
        quint32 count = it.value() % 10000;
        for (quint32 i = 0; i < count; ++i)
        {
            pev->append(this->words.at(idx + i));
        }
    }
    // 检索以此开头的

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

void SimpleSrc::_loadTxtFile(QFile *pf)
{
    QTextStream stream(pf);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    while(!stream.atEnd())
    {
        //QString line = codec->toUnicode(stream.readLine().toLocal8Bit());
        QString line = stream.readLine();
        QStringList kv = line.trimmed().split("\t");
        if (kv.length() < 2)
        {
            throw QString("无效的编码格式。%1").arg(line);
        }
        Global::SrcEle src;
        src.key = kv.at(1);
        //src.key = codec->toUnicode(kv.at(1).toLocal8Bit());
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
