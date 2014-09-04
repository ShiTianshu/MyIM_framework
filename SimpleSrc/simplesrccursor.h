#ifndef SIMPLESRCCURSOR_H
#define SIMPLESRCCURSOR_H

#include "../MyBase/global.h"

class SimpleSrcCursor : public Global::SrcCursor
{
public:
    SimpleSrcCursor();

    // SrcCursor interface
public:
    Global::SrcItem nextOne();
    QVector<Global::SrcItem> nextPage();
    void setKey(QString key);
    void setIndex(quint32 index);
    void setSrcs(QVector< Global::SrcItem > *pSrcs);
private:
    QString key;
    int index;
    void testHasNext();
    QVector< Global::SrcItem > *pSrcs;
};

#endif // SIMPLESRCCURSOR_H
