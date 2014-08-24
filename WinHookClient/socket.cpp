#include "socket.h"
#include <QLocalSocket>
#include <QDateTime>

QLocalSocket* gSocket;
qint64 gClientId = 0;

void RegisterClient()
{
    gSocket = new QLocalSocket();
    //gSocket->connectToServer(SERVER_NAME);
    gSocket->setServerName(SERVER_NAME);
    qDebug() << gSocket->serverName();
    qDebug() << gSocket->fullServerName();
    gSocket->connectToServer();
    qDebug() << gSocket->fullServerName();
    if (gSocket->waitForConnected())
    {
        gClientId = QDateTime::currentMSecsSinceEpoch();
        QString data = QString("%1|RC").arg(gClientId);
        gSocket->write(data.toLatin1());
        gSocket->flush();
    }
    else
    {
        qDebug() << "连接超时。" << gSocket->error() << gSocket->errorString();
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
