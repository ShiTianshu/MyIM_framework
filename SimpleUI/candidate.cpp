#include "candidate.h"

#include <QPainter>
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
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setFont(this->font);
        painter.setBrush(this->backgroundBrush);

        painter.drawRect(this->rect());

        painter.setPen(this->fontPen);
        painter.drawText(QPoint(100, 100), "ivtd今天");
    }
}
