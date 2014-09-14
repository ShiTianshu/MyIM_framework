#include "tabletranslator.h"
#include "../MyBase/global.h"
#include <QTime>

TableTranslator* GetInstance()
{
    return new TableTranslator;
}

TableTranslator::TableTranslator():
    IProc()
{
    this->name = "TableTranslator";
}

TableTranslator::~TableTranslator()
{

}

void TableTranslator::execute(InputContext *pic)
{
    if (!pic)
    {
        throw QString ("DefaultComposer没有找到上下文");
    }
    if (pic->composition.isEmpty())
    {
        // 跳过模块
        return;
    }
    if (!pic->key)
    {
        return;
    }
    if (pic->composition.length() > this->maxCodeLen)
    {
        // 顶屏
        QString comp = pic->composition.right(1);
        emit callAction("basics#push");
        pic->composition = comp;
    }
    pic->candidateList.clear();
    Global::SrcCursor *pCursor = 0;

    emit srcFind("tablesrc", pic->composition);
    emit srcCursor("tablesrc", &pCursor);

    qDebug() << "has next: " << pCursor->hasNext();
    // 获得第一页的候选。
    if (pCursor->hasNext())
    {
        pic->candidateList += pCursor->nextPage();
        pic->pageIndex = 0;
    }

    qDebug() << pic->candidateList;

    if (pic->composition.length() >= this->maxCodeLen &&
            pic->candidateList.size() == 1)
    {
        emit callAction("basics#push");
    }
}

void TableTranslator::initialize(const QMap<QString, QVariant> &envs)
{
    this->maxCodeLen = this->getIdConfig(envs, "maxCodeLen").toInt();
}
