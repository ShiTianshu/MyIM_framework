#include <QApplication>
#include "hook.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HookKeyboard();
    return a.exec();
}
