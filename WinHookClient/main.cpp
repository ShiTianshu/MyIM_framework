#include <QApplication>
#include "hook.h"
#include "socket.h"
#include <QDebug>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
