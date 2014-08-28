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
    if (!pic)
    {
        throw QString ("DefaultComposer没有找到上下文");
    }
    qDebug() << "DefaultComposer begin ----------" << pic->key;
    if (pic->key == 0) return;
    // 只处理键按下的事件。
    if (pic->keyPress)
    {
        // 如果是ctrl, alt, shift, win放行
        if (((pic->keyFlags) & (CONTROL_FLAG)) != 0)
        {
            pic->accepted = false;
            pic->key = 0;
        }
        else if (((pic->keyFlags) & (MENU_FLAG)) != 0)
        {
            pic->accepted = false;
            pic->key = 0;
        }
        else if (((pic->keyFlags) & (SHIFT_FLAG)) != 0)
        {
            pic->accepted = false;
            pic->key = 0;
        }
        else if (((pic->keyFlags) & (SPECIAL_FLAG)) != 0)
        {
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
        else if (pic->key >= Qt::Key_A && pic->key <= Qt::Key_Z)
        {
            pic->accepted = true;
            pic->composition += QChar(pic->key).toLower();
        }
        else if (pic->key == Qt::Key_Semicolon)
        {
            pic->accepted = true;
            pic->composition += ';';
        }
        else if (pic->key == Qt::Key_Comma ||
                 pic->key == Qt::Key_Period ||
                 pic->key == Qt::Key_Apostrophe ||
                 pic->key == Qt::Key_Minus ||
                 pic->key == Qt::Key_Plus ||
                 pic->key == Qt::Key_Backslash ||
                 pic->key == Qt::Key_Slash ||
                 pic->key == Qt::Key_BracketLeft ||
                 pic->key == Qt::Key_BraceRight ||
                 pic->key == Qt::Key_QuoteLeft)
        {
            if (!pic->candidateList.isEmpty())
            {
                emit action("basics#push");
            }
            pic->accepted = false;
            pic->key = 0;
        }
        else if (pic->key >= Qt::Key_0 && pic->key <= Qt::Key_9)
        {
            if (pic->key == Qt::Key_0)
            {
                qDebug() << "数字键0";
                if (pic->composition.isEmpty())
                {
                    pic->accepted = false;
                    pic->key = 0;
                }
                else
                {
                    emit action("basics#clear");
                }
            }
            else
            {
                qDebug() << "数字键1-9键选" << pic->key - Qt::Key_1;
                emit action(QString("basics#select%1").arg(pic->key - Qt::Key_1));
            }
        }
        else if (pic->key == Qt::Key_Space)
        {
            if (pic->composition.isEmpty())
            {
                pic->accepted = false;
                pic->key = 0;
            }
            else
            {
                emit action("basics#select0");
            }
        }
        else if (pic->key == Qt::Key_Escape)
        {
            if (pic->composition.isEmpty())
            {
                pic->accepted = false;
                pic->key = 0;
            }
            else
            {
                emit action("basics#clear");
            }
        }
        else if (pic->key == Qt::Key_Backspace)
        {
            qDebug() << "backspace ----- ";
            if (pic->composition.isEmpty())
            {
                pic->accepted = false;
                pic->key = 0;
            }
            else
            {
                emit action("basics#back");
            }
        }
        else if (pic->key == Qt::Key_Return)
        {
            if (pic->composition.isEmpty())
            {
                pic->accepted = false;
                pic->key = 0;
            }
            else
            {
                emit action("basics#sendcomp");
            }
        }
        else
        {
            pic->accepted = false;
            pic->key = 0;
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
