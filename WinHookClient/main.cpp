#include <QApplication>
#include "hook.h"
#include "socket.h"
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    try
    {
        HookKeyboard();
        RegisterClient();
        //SendKeyUp(65, 0);
        //UnregisterClient();
    }
    catch(QString exception)
    {
        QMessageBox::warning(0, "出错了", exception);
    }
    return a.exec();
}
