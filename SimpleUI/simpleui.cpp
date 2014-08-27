#include "simpleui.h"

#include <QColor>
#include <QDebug>

SimpleUI *GetInstance()
{
    return new SimpleUI;
}

SimpleUI::SimpleUI():
    IProc()
{
    this->name = "SimpleUI";
    this->pcand = 0;
}

SimpleUI::~SimpleUI()
{

}

void SimpleUI::initialize(const QMap<QString, QVariant> &envs)
{
    if (!this->pcand)
    {
        this->pcand = new Candidate;
    }
    // 读取颜色
    QString background = this->getIdConfig(envs, "background").toString();
    this->pcand->backgroundBrush = QBrush(QColor(background));
    qDebug() << background;

    QString currentFront = this->getIdConfig(envs, "currentfront").toString();
    qDebug() << "currentFront";
    pcand->currentPen = QPen(QColor(currentFront));

    QString currentBackground = this->getIdConfig(envs, "currentbackground").toString();
    pcand->currentBrush = QBrush(QColor(currentBackground));

    QString shadowWidth = this->getIdConfig(envs, "shadowwidth").toString();
    pcand->shadowWidth = shadowWidth.toInt();

    QString borderRadius = this->getIdConfig(envs, "borderradius").toString();
    pcand->borderRadius = borderRadius.toInt();

    QString borderPadding = this->getIdConfig(envs, "borderpadding").toString();
    pcand->borderPadding = borderPadding.toInt();

    QString shadowColor = this->getIdConfig(envs, "shadowcolor").toString();
    pcand->shadowColor = QColor(shadowColor);

    QString compColor = this->getIdConfig(envs, "compcolor").toString();
    pcand->compPen = QPen(QColor(compColor));

    // 读取字体信息
    int fontSize = this->getIdConfig(envs, "fontsize").toInt();
    QString fontFamily = this->getIdConfig(envs, "fontfamily").toString();
    pcand->font = QFont(fontFamily, fontSize);

    QString fontColor = this->getIdConfig(envs, "fontcolor").toString();
    pcand->fontPen = QPen(QColor(fontColor));

    // 边框宽度
    pcand->minWidth = this->getIdConfig(envs, "minwidth").toInt();
    pcand->show();
}

void SimpleUI::execute(InputContext *pic)
{
    qDebug() << "execute UI";
    if (!this->pcand)
    {
        throw QString ("Candidate没有初始化。");
    }
    this->pcand->setInputContext(pic);
    if (!pic->composition.isEmpty())
    {
        qDebug() << "page index" << pic->pageIndex;
        uint start = pic->pageIndex * 5;
        pcand->cands.clear();
        qDebug() << "start:" << start << "candsize:" << pic->candidateList.size();
        for (int i = start; i < pic->candidateList.size(); ++i)
        {
            qDebug() << "add cand";
            pcand->cands.append(QString("%1.%2").arg(i+1).arg(pic->candidateList.at(i).value));
        }
//        pcand->cands.append("1.测试内容很长的时候，效果怎么样。我很长啊我很长。");
//        pcand->cands.append("2.你好");
        qDebug() << pcand->cands;
        if (this->pcand->isVisible())
        {
            this->pcand->update();
        }
        else
        {
            this->pcand->show();
        }
    }
    else
    {
        this->pcand->hide();
    }
}




