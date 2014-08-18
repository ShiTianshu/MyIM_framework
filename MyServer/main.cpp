#include "myserver.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    try
    {
        MyServer server;
        server.initialize();
    }
    catch (QString exception)
    {
        QMessageBox::information(0, "出错了", exception);
        return 1;
    }
    return a.exec();
}
