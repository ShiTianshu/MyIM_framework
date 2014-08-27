#include "defaultcomposer.h"
#include "../MyBase/global.h"
#include <QDebug>

DefaultComposer *GetInstance()
{
    return new DefaultComposer;
}

DefaultComposer::DefaultComposer():
    IProc()
{
    this->name = "DefaultComposer";
}

DefaultComposer::~DefaultComposer()
{

}

void DefaultComposer::execute(InputContext *pic)
{
    qDebug() << "default composer invoked, key:" << pic->key;
    qDebug() << "flags:" << pic->keyFlags;
    if (pic->key == 0) return;
    // 只处理键按下的事件。
    if (pic->keyPress)
    {
        // 如果是ctrl, alt, shift, win放行
        if (((pic->keyFlags) & (CONTROL_FLAG)) != 0)
        {
            qDebug() << "ctrl down";
            pic->accepted = false;
            pic->key = 0;
        }
        else if (((pic->keyFlags) & (MENU_FLAG)) != 0)
        {
            qDebug() << "menu down";
            pic->accepted = false;
            pic->key = 0;
        }
        else if (((pic->keyFlags) & (SHIFT_FLAG)) != 0)
        {
            qDebug() << "shift down";
            pic->accepted = false;
            pic->key = 0;
        }
        else if (((pic->keyFlags) & (SPECIAL_FLAG)) != 0)
        {
            qDebug() << "spec down";
            pic->accepted = false;
            pic->key = 0;
        }
        else if (pic->key == Qt::Key_Control ||
                 pic->key == Qt::Key_Shift ||
                 pic->key == Qt::Key_Menu ||
                 pic->key == Qt::Key_Meta)
        {
            pic->accepted = false;
            pic->key = 0;
        }
        else
        {
            qDebug() << "accepted";
            pic->accepted = true;
            pic->composition += QChar(pic->key).toLower();
            //qDebug() << pic->key;
        }
    }
    else
    {
        qDebug() << "pass key up";
        pic->accepted = false;
        pic->key = 0;
    }
}

void DefaultComposer::initialize(const QMap<QString, QVariant> &)
{

}
