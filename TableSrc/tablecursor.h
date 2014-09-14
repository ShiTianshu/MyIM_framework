#ifndef TABLECURSOR_H
#define TABLECURSOR_H

#include "../MyBase/global.h"

class TableCursor : public Global::SrcCursor
{
public:
    TableCursor();

    // SrcCursor interface
public:
    Global::SrcItem nextOne();
    QVector<Global::SrcItem> nextPage();

public:
    int index;
    QString key;
    QVector< Global::SrcItem > *pdatas;
};

#endif // TABLECURSOR_H
