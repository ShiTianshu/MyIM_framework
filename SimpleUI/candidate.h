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
    int shadowWidth;        // 阴影的边框宽度
    int borderRadius;       // 边框的圆角
    int borderPadding;      // 边框留空
    QColor shadowColor;     // 阴影的颜色
    QBrush backgroundBrush; // 背影颜色
    QFont font;             // 字体
    QPen fontPen;           // 默认前景色
    QBrush currentBrush;    // 当前选项的背景色
    QPen currentPen;        // 当前选项的前景色
    QPen compPen;           // 编码颜色
    QVector< QString > cands;
    int minWidth;
protected:
    void paintEvent(QPaintEvent *);
private:
    InputContext *pic;
};

#endif // CANDIDATE_H
