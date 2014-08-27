#include "inputcontext.h"

#include <QDebug>

InputContext::InputContext(qint64 id)
{
    this->id = id;
    qDebug() << QString("创建上下文，ID=%1").arg(this->id);
    this->resetAll();
}

InputContext::~InputContext()
{
    qDebug() << QString("销毁上下文，ID=%1").arg(this->id);
}

void InputContext::resetKeys()
{
    this->key = 0;
    this->keyPress = false;
    this->keyFlags = 0;
    this->keycode = 0;
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
    this->editText.clear();
    this->pageIndex = 0;
    this->accepted = false;
    this->selectIndex = 0;
}

void InputContext::resetAll()
{
    this->resetKeys();
    this->resetInfos();
}
