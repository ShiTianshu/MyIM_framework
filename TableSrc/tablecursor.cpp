#include "tablecursor.h"

TableCursor::TableCursor()
{
    this->pdatas = 0;
    this->index = -1;
    this->_hasNext = false;
}

Global::SrcItem TableCursor::nextOne()
{
    if (!this->_hasNext)
    {
        throw QString("hasNext()为false时，调用了next方法？");
    }
    qDebug() << "test has next" << (index + 1 < this->pdatas->length())
             << this->pdatas->at(index + 1).key.startsWith(this->key) << this->key
                << this->pdatas->at(index + 1).key;
    if (index + 1 < this->pdatas->length() && this->pdatas->at(index + 1).key.startsWith(this->key))
    {
        this->_hasNext = true;
    }
    else
    {
        this->_hasNext = false;
    }
    return this->pdatas->at(index ++);
}

QVector<Global::SrcItem> TableCursor::nextPage()
{
    QVector< Global::SrcItem > items;
    for (int i = 0; i < this->pageSize && this->hasNext(); ++i)
    {
        items.append(this->nextOne());
    }
    return items;
}
