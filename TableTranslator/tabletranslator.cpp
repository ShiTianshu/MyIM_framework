#include "tabletranslator.h"
#include "../MyBase/global.h"

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
        QString comp = pic->composition.left(1);
        emit action("basics#push");
        pic->composition = comp;
    }
    pic->candidateList.clear();
    QVector< Global::SrcEle > v;
    emit find("tablesrc", pic->composition, &v);
    if (!v.isEmpty())
    {
        pic->candidateList += v;
    }
    if (pic->composition.length() >= this->maxCodeLen &&
            pic->candidateList.size() == 1)
    {
        emit action("basics#push");
    }
}

void TableTranslator::initialize(const QMap<QString, QVariant> &envs)
{
    this->maxCodeLen = this->getIdConfig(envs, "maxCodeLen").toInt();
}
