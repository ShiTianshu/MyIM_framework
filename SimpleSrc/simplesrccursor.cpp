#include "simplesrccursor.h"

SimpleSrcCursor::SimpleSrcCursor()
{
    this->pSrcs = 0;
    this->index = -1;
    this->_hasNext = false;
}

Global::SrcItem SimpleSrcCursor::nextOne()
{
    if (!this->pSrcs)
    {
        throw QString ("没有为游标设置数据源！");
    }
    if (this->index >= pSrcs->size())
    {
        throw QString ("数据源下标越界！");
    }
    if (this->hasNext())
    {
        this->testHasNext();
        return pSrcs->at(this->index++);
    }
    else
    {
        throw QString  ("数据源无法取得数据，当前数据和当前编码不一致。");
    }
}

QVector<Global::SrcItem> SimpleSrcCursor::nextPage()
{
    QVector< Global::SrcItem > v;
    if (!this->pSrcs)
    {
        throw QString ("没有为游标设置数据源！");
    }
    for (int i = 0; i < this->pageSize; ++i)
    {
        if (this->hasNext())
        {
            v.append(this->nextOne());
        }
        else
        {
            break;
        }
    }
    return v;
}

void SimpleSrcCursor::setKey(QString key)
{
    this->key = key;
    this->testHasNext();
}

void SimpleSrcCursor::setIndex(quint32 index)
{
    this->index = index;
    this->testHasNext();
}

void SimpleSrcCursor::setSrcs(QVector<Global::SrcItem> *pSrcs)
{
    this->pSrcs = pSrcs;
    this->testHasNext();
}

void SimpleSrcCursor::testHasNext()
{
    if (!this->key.isEmpty() && this->pSrcs && this->index >= 0)
    {
        this->_hasNext = false;
        if (this->index < this->pSrcs->size()
                && this->pSrcs->at(this->index).key.startsWith(this->key))
        {
            this->_hasNext = true;
        }
    }
}


