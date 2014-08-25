#include "myserver.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>
#include <QLocalServer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyServer server;
    try
    {
        server.initialize();
        qDebug() << "initialize结束";
        return a.exec();
    }
    catch (QString exception)
    {
        QMessageBox::information(0, "出错了", exception);
    }
    return 1;
}
