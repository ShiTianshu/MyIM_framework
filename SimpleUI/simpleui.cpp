#include "simpleui.h"

#include <QColor>

SimpleUI *GetInstance(QString modId)
{
    return new SimpleUI(modId);
}

SimpleUI::SimpleUI(QString id):
    IProc(id)
{
    this->name = "SimpleUI";
}

SimpleUI::~SimpleUI()
{

}

void SimpleUI::initialize(const QMap<QString, QVariant> &envs)
{
    if (!this->pcand)
    {
        pcand = new Candidate;
    }
    // 读取颜色
    QString background = this->getIdConfig(envs, "background").toString();
    pcand->backgroundBrush = QBrush(QColor(background));

    // 读取字体信息
    int fontSize = this->getIdConfig(envs, "fontsize").toInt();
    QString fontFamily = this->getIdConfig(envs, "fontfamily").toString();
    pcand->font = QFont(fontFamily, fontSize);
    QString fontColor = this->getIdConfig(envs, "fontcolor").toString();
    pcand->fontPen = QPen(QColor(fontColor));

    pcand->show();
}

void SimpleUI::execute(InputContext *pic)
{
    if (!this->pcand)
    {
        throw QString ("Candidate没有初始化。");
    }
    pic->composition = "ivtd";
    this->pcand->setInputContext(pic);
    this->pcand->repaint();
}




