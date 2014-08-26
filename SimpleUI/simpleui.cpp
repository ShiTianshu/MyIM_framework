#include "simpleui.h"

#include <QColor>
#include <QDebug>

SimpleUI *GetInstance(QString modId)
{
    return new SimpleUI(modId);
}

SimpleUI::SimpleUI(QString id):
    IProc(id)
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
    qDebug() << "execute UI";
    if (!this->pcand)
    {
        throw QString ("Candidate没有初始化。");
    }
    this->pcand->setInputContext(pic);
    if (pic->keycode == 65)
    {
        this->pcand->show();
        if (this->pcand->isVisible())
        {
            this->pcand->repaint();
        }
        pic->accepted = false;
    }
    else
    {
        this->pcand->hide();
        pic->accepted = true;
    }
    qDebug() << pic->accepted << "accepted";
}




