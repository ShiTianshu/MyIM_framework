#include "socket.h"
#include <QLocalSocket>
#include <QDateTime>

QLocalSocket* gSocket;
qint64 gClientId = 0;

void RegisterClient()
{
//    gSocket = new QLocalSocket();
//    gSocket->connectToServer(SERVER_NAME);
//    if (gSocket->waitForConnected())
//    {
//        qDebug() << "连接成功。";
//        gClientId = QDateTime::currentMSecsSinceEpoch();
//        QString data = QString("%1|RC").arg(gClientId);
//        gSocket->write(data.toLatin1());
//        gSocket->flush();
//    }
//    else
//    {
//        qDebug() << "连接超时。" << gSocket->error() << gSocket->errorString();
//    }
    //QLocalSocket socket;
    QLocalSocket socket;
    socket.connectToServer("myim_server");
    if (socket.waitForConnected())
    {
        qDebug() << "t";
    }
    else
    {
        qDebug() << "F";
    }
}


void UnregisterClient()
{
    if (gSocket)
    {
        QString data = QString("%1|UC").arg(gClientId);
        gSocket->write(data.toLatin1());
        gSocket->flush();
        gSocket->close();
        delete gSocket;
        gSocket = 0;
        gClientId = 0;
    }
}


void SendKeyUp(char keycode, uint flags)
{

}


void SendKeyDown(char keycode, uint flags)
{

}


void ChangePos(uint x, uint y)
{

}
