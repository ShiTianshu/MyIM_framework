#include "candidate.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QStaticText>

Candidate::Candidate(QWidget *parent) :
    QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
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
        QPoint pos = pic->caretPos;
        if (pos.x() != 0 || pos.y() !=0)
        {
            this->move(pos);
        }
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QFontMetrics metrics(this->font);
        int width = metrics.width(pic->composition);
        int fontHeight = metrics.height();
        // 获得需要显示的宽度
        for (int i = 0; i < this->cands.size(); ++i)
        {
            int t = metrics.width(this->cands.at(i));
            t += metrics.width(this->tips.at(i));
            width = width > t ? width : t;
        }
        width = width > this->minWidth ? width : this->minWidth;
        int lineSpace = fontHeight / 3;
        int height = fontHeight * (this->cands.size() + 1) + this->cands.size() * lineSpace;
        width += 4 * this->borderPadding;
        height += 2 * this->borderPadding;
        resize(width + 2 * this->shadowWidth, height + 2 * this->shadowWidth);
        QPainterPath path;
        path.addRoundedRect(this->shadowWidth, this->shadowWidth,
                            width,
                            height,
                            this->borderRadius, this->borderRadius);
        painter.fillPath(path, this->backgroundBrush);
        // 画阴影
        for (int i = 1; i <= this->shadowWidth; ++i)
        {
            this->shadowColor.setAlpha(60 / i);
            path.addRoundedRect(this->shadowWidth - i, this->shadowWidth - i,
                                this->width() - 2 * (this->shadowWidth - i),
                                this->height()- 2 * (this->shadowWidth - i),
                                this->borderRadius + i, this->borderRadius + i);
            painter.setPen(QPen(QBrush(this->shadowColor), 1));
            painter.drawPath(path);
        }
        // 画编码
        painter.setFont(this->font);
        painter.setPen(this->compPen);
        painter.drawStaticText(this->borderPadding * 2 + this->shadowWidth,
                               this->borderPadding + this->shadowWidth,
                               QStaticText(pic->composition));
        painter.setPen(this->fontPen);
        // 候选

        int left = 2 * this->borderPadding + this->shadowWidth;
        int top = this->borderPadding + this->shadowWidth;
        for (int i = 0; i < this->cands.size(); ++i)
        {
            if (!i)
            {
                painter.setPen(this->currentPen);
            }
            else
            {
                painter.setPen(this->fontPen);
            }
            top += lineSpace + fontHeight;
            painter.drawStaticText(left, top, QStaticText(this->cands.at(i)));
            painter.setPen(this->tipPen);
            painter.drawStaticText(left+metrics.width(this->cands.at(i)),
                                   top, QStaticText(this->tips.at(i)));

        }

    }
}
