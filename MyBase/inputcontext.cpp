#include "inputcontext.h"

#include <QDebug>

InputContext::InputContext(ulong id)
{
    this->id = id;
    qDebug() << QString("创建上下文，ID=%1").arg(this->id);
}

InputContext::~InputContext()
{
    qDebug() << QString("销毁上下文，ID=%1").arg(this->id);
}

void InputContext::resetKeys()
{
    this->key = 0;
    this->keyPress = false;
}

void InputContext::resetInfos()
{
    this->candidateList.clear();
    this->caretPos = QPoint(0, 0);
    this->commitString.clear();
    this->compIndex = 0;
    this->composition.clear();
    this->currentMatched.clear();
    this->extInfo.clear();
    this->originalMatched.clear();
    this->textEdit.clear();
    this->pageIndex = 0;
}

void InputContext::resetAll()
{
    this->resetKeys();
    this->resetInfos();
}
