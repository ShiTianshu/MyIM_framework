#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H

#include <QPoint>
#include <QString>
#include "global.h"


/**
 * @brief The InputContext class
 * 输入法上下文
 * 每一个核心有一个存储上下文的map，一个进程有且只有一个上下文。
 * 当前的按键信息，会被填入key, keyPress
 * 当前的光标位置可以得到时，会被填入caretPos
 * 最终的处理结果，存入 textEdit和commitString
 */
class InputContext
{
public:
    InputContext(qint64 id);
    ~InputContext();
    qint64 id;              // 上下文id，对应进程。
    uint keycode;
    int key;                // 当前的按键
    bool keyPress;          // 当前按键是否是按下的。
    uint keyFlags;          // 功能键标志位，用来判断ctrl,alt,shift,win(command)等等。
    QString composition;    // 当前编码。
    QVector< Global::SrcItem* > candidateList;  // 候选列表。
    QVector< Global::SrcItem* > originalMatched;// 原匹配，用于整句
    QVector< Global::SrcItem* > currentMatched; // 当前匹配，用于整句
    uint pageIndex;         // 候选页码。
    QString editText;       // 嵌入编码。
    QString commitString;   // 上屏内容。
    uint compIndex;         // 编码光标，用于整句。
    uint selectIndex;       // 选择候选的光标。
    QPoint caretPos;        // 光标位置。
    QMap< QString, QVariant > extInfo;  // 额外信息。
    bool accepted;          // 是否处理了按键。如果处理了就吃掉。

    void resetKeys();       // 清空按键
    void resetInfos();      // 清空信息
    void resetAll();        // 清空全部
    void resetResponse();   // 清空响应
};

#endif // INPUTCONTEXT_H
