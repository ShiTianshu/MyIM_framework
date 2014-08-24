#include <QApplication>
#include "hook.h"
#include "socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //HookKeyboard();
    RegisterClient();
    return a.exec();
}
