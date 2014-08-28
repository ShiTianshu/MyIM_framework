#include "basics.h"

Basics* GetInstance()
{
    return new Basics;
}

Basics::Basics():
    IActGroup()
{
    this->name = "Basics";
}

Basics::~Basics()
{

}

void Basics::initialize(const QMap<QString, QVariant> &)
{

}

void Basics::executeGroup(QString arg, InputContext *pic)
{
    qDebug() << "basics#" << arg;
    if (arg == "push")  // 上屏
    {
        qDebug() << "push comp->" << pic->composition;
        if (pic->composition.isEmpty())
        {
            // 没有编码输入时，放行。
            pic->key = 0;
            pic->accepted = false;
        }
        else if (pic->candidateList.isEmpty())
        {
            pic->resetInfos();
        }
        else
        {
            // 获得当前的候选
            int idx = pic->pageIndex * 5 + pic->selectIndex;
            if (idx >= pic->candidateList.size())
            {
                throw QString ("上屏时下标异常，指向%1，但是总数为%2").arg(idx).arg(pic->candidateList.size());
            }
            QString current = pic->candidateList.at(idx).value;
            pic->commitString += current;
            pic->resetInfos();
            qDebug() << "commit" << pic->commitString;
        }
    }
    else if (arg == "clear")  // 清空
    {
        pic->resetInfos();
    }
    else if (arg == "back")  // 回退，如果有编码删除编码，如果没有编码放行。
    {
        qDebug() << "inback";
        if (pic->composition.isEmpty())
        {
            pic->accepted = false;
            pic->resetInfos();
            pic->key = 0;
        }
        else
        {
            qDebug() << "删除编码1" << pic->composition;
            pic->composition = pic->composition.left(pic->composition.size() - 1);
            pic->accepted = true;
            qDebug() << "删除编码2" << pic->composition;
        }
    }
    else if (arg.startsWith("select"))
    {
        int idx = arg.right(1).toInt();
        idx += pic->pageIndex * 5;
        if (idx < pic->candidateList.size())
        {
            QString current = pic->candidateList.at(idx).value;
            pic->commitString = current;
            pic->resetInfos();
        }
    }
    else if (arg == "sendcomp")
    {
        pic->commitString = pic->composition;
        pic->resetInfos();
    }
    else
    {
        throw QString ("basics不支持参数%1").arg(arg);
    }
}

void Basics::execute(InputContext *)
{

}
