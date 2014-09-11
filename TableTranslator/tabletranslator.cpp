#include "tabletranslator.h"
#include "../MyBase/global.h"
#include "../SimpleSrc/simplesrccursor.h"
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
    if (pic->composition.length() > this->maxCodeLen)
    {
        // 顶屏
        QString comp = pic->composition.right(1);
        emit toAction("basics#push");
        pic->composition = comp;
    }
    pic->candidateList.clear();
    Global::SrcCursor *pCursor = 0;
    emit toFind("tablesrc", pic->composition, &pCursor);
    for (int i = 0; i < 10; ++i)
    {
        if (pCursor->hasNext())
        {
            pic->candidateList += pCursor->nextPage();
        }
        else
        {
            break;
        }
    }
    if (pic->composition.length() >= this->maxCodeLen &&
            pic->candidateList.size() == 1)
    {
        emit toAction("basics#push");
    }
}

void TableTranslator::initialize(const QMap<QString, QVariant> &envs)
{
    this->maxCodeLen = this->getIdConfig(envs, "maxCodeLen").toInt();
}
