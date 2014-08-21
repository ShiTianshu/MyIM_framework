#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H

#include <QPoint>
#include <QString>
#include "global.h"


/** --------------------------------------------------------------------
 * @brief The InputContext class
 * 输入法上下文
 * 每一个核心有一个存储上下文的map，一个进程有且只有一个上下文。
 * 当前的按键信息，会被填入key, keyPress
 * 当前的光标位置可以得到时，会被填入caretPos
 * 最终的处理结果，存入 textEdit和commitString
 * ---------------------------------------------------------------------
 */
class InputContext
{
public:
    InputContext(ulong id);
    ~InputContext();
    ulong id;               // 上下文id，对应进程。
    char key;               // 当前的按键。
    bool keyPress;          // 当前按键是否是按下的。
    QString composition;    // 当前编码。
    QVector< Global::SrcEle* > candidateList;  // 候选列表。
    QVector< Global::SrcEle* > originalMatched;// 原匹配，用于整句
    QVector< Global::SrcEle* > currentMatched; // 当前匹配，用于整句
    uint pageIndex;         // 候选页码。
    QString textEdit;       // 嵌入编码。
    QString commitString;   // 上屏内容。
    uint compIndex;         // 编码光标，用于整句。
    QPoint caretPos;        // 光标位置。
    QMap< QString, QVariant > extInfo;  // 额外信息。

    void resetKeys();       // 清空按键
    void resetInfos();      // 清空除按键外的全部
    void resetAll();        // 清空全部
};

#endif // INPUTCONTEXT_H
