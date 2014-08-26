#include "candidate.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

Candidate::Candidate(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->pic = 0;
}

Candidate::~Candidate()
{

}

void Candidate::setInputContext(InputContext *pic)
{
    this->pic = pic;
}

void Candidate::paintEvent(QPaintEvent *)
{
    qDebug() << "cand paint event";
    if (!this->pic)
    {
        // 启动时
        this->hide();
    }
    else
    {
        pic->composition = "ivtd";
        //获得这一页的候选。
        int start = pic->pageIndex * 5;
        QVector< QString > cands;   // 当前要显示的候选。
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        // 计算内容的宽高。
        cands.append("世界");cands.append("你好");
        int len = pic->composition.size();
        for (int i = start; i < pic->candidateList.size(); ++i)
        {
            cands.append(pic->candidateList.at(i)->value);
            int t = pic->candidateList.at(i)->value.size();
            if (t > len) len = t;
        }
        int lineSpace = this->font.pointSize() / 5; // 行间距
        int width = len * (this->font.pointSize() + lineSpace) + 2 * this->borderPadding;
        int height = cands.size() * (this->font.pointSize() + lineSpace) + 2 * this->borderPadding;
        if (this->width() - 2 * this->shadowWidth != width || this->height() - 2 * this->shadowWidth != height)
        {
            this->resize(2 * this->shadowWidth + width, 2 * this->shadowWidth + height);
        }
        // 画背景
        QPainterPath path;
        path.addRoundedRect(this->shadowWidth, this->shadowWidth,
                            this->width() - 2 * this->shadowWidth,
                            this->height()- 2 * this->shadowWidth,
                            this->borderRadius, this->borderRadius);
        painter.setPen(this->backgroundBrush.color());
        painter.fillPath(path, this->backgroundBrush);
        // 画阴影
        for (int i = 1; i < this->shadowWidth; ++i)
        {
            this->shadowColor.setAlpha(100 - (100 / this->shadowWidth) * i);
            //QPen _shadow(QColor(this->shadowPen.color().red(), this->shadowPen.color().green(), this->shadowPen.color().blue(), 255 - (255 / this->shadowWidth) * i));
            path.addRoundedRect(this->shadowWidth - i, this->shadowWidth - i,
                                this->width() - 2 * (this->shadowWidth - i),
                                this->height()- 2 * (this->shadowWidth - i),
                                this->borderRadius, this->borderRadius);
            painter.setPen(QPen(QBrush(this->shadowColor), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawPath(path);
        }
        painter.setFont(this->font);
        painter.setPen(this->fontPen);
        painter.drawText(QPoint(this->borderPadding , this->borderPadding),pic->composition);
        //int currentPadding = this->font.pointSize() / 5; // 当前字体大小下的首选背景到字体的留空。
        // 画候选
        int y = this->borderPadding + this->font.pointSize() + lineSpace;
        int x = this->borderPadding;
        for (int i = 0; i < cands.size(); ++i)
        {
            painter.drawText(x, y, cands.at(i));
            y += this->font.pointSize() + lineSpace;
        }
    }
}
