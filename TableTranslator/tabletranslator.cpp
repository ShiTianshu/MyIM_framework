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
    if (!pic->key)
    {
        // 跳过模块
        return;
    }
    qDebug() << "translator begin";
    pic->candidateList.clear();
    if (pic->composition.length() > 5)
    {
        // 顶屏
        pic->composition = pic->composition.left(1);
    }
    QVector< Global::SrcEle > v;
    emit find("tablesrc", pic->composition, &v);
    if (!v.isEmpty())
    {
        pic->candidateList += v;
    }
    qDebug() << pic->candidateList.size();
}

void TableTranslator::initialize(const QMap<QString, QVariant> &envs)
{
    this->maxCodeLen = this->getIdConfig(envs, "maxCodeLen").toInt();
}
