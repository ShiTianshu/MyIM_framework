#include "tablesrc.h"
#include <QRegExp>


TableSrc* GetInstance()
{
    return new TableSrc;
}

TableSrc::TableSrc()
{
    this->name = "tablesrc";
    this->cursor.pageSize = 5;
    this->cursor.pdatas = &(this->datas);
}

TableSrc::~TableSrc()
{

}


//+-----------------------------------------------------------------------------
//
// 排序用的方法。
//
//------------------------------------------------------------------------------

bool SrcLessThan(const Global::SrcItem &item1, const Global::SrcItem &item2)
{
    return item1.key < item2.key;
}


void TableSrc::initialize(const QMap<QString, QVariant> &env)
{
    this->fileName = this->getIdConfig(env, "file").toString();
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
        qDebug() << "bin读取完成";
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
    qDebug() << "src initialize finished! size:" << this->datas.size();
}

void TableSrc::find(QString key)
{
    qDebug() << "start find";

    int result = this->_binSearch(key, false);

    if (result == -1)
    {
        result = this->_binSearch(key, true);
    }
    // 扩展
    qDebug() << "extending...";

    if (result == -1)
    {

        // 没有找到。
        this->cursor._hasNext = false;
        this->cursor.index = -1;
        this->cursor.key = "";
    }
    else
    {
        qDebug() << "found item" << this->datas.at(result);
        this->cursor._hasNext = true;
        this->cursor.index = result;
        this->cursor.key = key;
    }
}

void TableSrc::srcCursor(Global::SrcCursor **ppcurr)
{
    *ppcurr = &(this->cursor);
}

void TableSrc::remove(uint)
{

}

void TableSrc::insert(QString, QString, QVariant)
{

}

void TableSrc::_loadBinFile(QFile *pf)
{
    QDataStream stream(pf);
    stream >> this->datas;
}

void TableSrc::_createBinFile(QFile *pf)
{
    QDataStream stream(pf);
    stream << this->datas;
}

void TableSrc::_loadTxtFile(QFile *pf)
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
        Global::SrcItem item;
        item.key = kv.at(1);
        item.value = kv.at(0);
        this->datas.append(item);
    }
    qStableSort(this->datas.begin(), this->datas.end(), SrcLessThan);
}

//+-----------------------------------------------------------------------------
//
// 二分查找
//
//------------------------------------------------------------------------------

/**
 * @brief TableSrc::_binSearch
 * @param key
 * @return 返回编码，以该编码为开头的，最长的编码的位置。
 */
int TableSrc::_binSearch(QString key, bool ext)
{
    qDebug() << "binsearch";
    int len = key.length();
    // 可以取到l不可以取到h
    int l = 0;
    int h = this->datas.length();
    int m = 0;
    while (l < h)
    {
        m = (h + l) / 2;
        QString t;
        if (!ext)
        {
            t = this->datas.at(m).key;
        }
        else
        {
            t = this->datas.at(m).key.left(len);
        }

        if (t == key)
        {
            break;
        }
        else if (t > key)
        {
            h = m;
        }
        else
        {
            l = m + 1;
        }
    }
    if (l >= h)
    {
        // 没有找到。
        return -1;
    }
    else
    {
        // 向回递推，找到与之相同编码的第一条。
        while (m > 0)
        {
            if (this->datas.at(m - 1).key.leftRef(len) == key)
            {
                --m;
            }
            else
            {
                break;
            }
        }
        return m;
    }
}




