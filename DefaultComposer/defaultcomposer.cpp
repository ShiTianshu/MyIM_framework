#include "defaultcomposer.h"
#include "../MyBase/global.h"
#include <QDebug>

DefaultComposer *GetInstance(QString modId)
{
    return new DefaultComposer(modId);
}

DefaultComposer::DefaultComposer(QString id):
    IProc(id)
{
    this->name = "DefaultComposer";
}

DefaultComposer::~DefaultComposer()
{

}

void DefaultComposer::execute(InputContext *pic)
{
    // 只处理键按下的事件。
    if (pic->keyPress)
    {
        // 如果是ctrl, alt, shift, win放行

        qDebug() << pic->key;
        pic->accepted = true;
    }
}

void DefaultComposer::initialize(const QMap<QString, QVariant> &)
{

}
