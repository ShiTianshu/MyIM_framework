#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include "../MyBase/inputcontext.h"

class Candidate : public QWidget
{
    Q_OBJECT
public:
    explicit Candidate(QWidget *parent = 0);
    ~Candidate();
    void setInputContext(InputContext *pic);
    // 显示参数
    QBrush backgroundBrush;
    QFont font;
    QPen fontPen;
protected:
    void paintEvent(QPaintEvent *);
private:
    InputContext *pic;
};

#endif // CANDIDATE_H
