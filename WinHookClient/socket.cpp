#include "socket.h"
#include <QLocalSocket>
#include <QDateTime>

QLocalSocket* gSocket;
qint64 gClientId = 0;

void RegisterClient()
{
    if (gSocket)
    {
        throw QString("已经注册了");
    }
    gSocket = new QLocalSocket();
    gSocket->connectToServer(SERVER_NAME);
    if (gSocket->waitForConnected())
    {
        qDebug() << "连接成功";
        gClientId = QDateTime::currentMSecsSinceEpoch();
        QString data = Global::RegisterClientData(gClientId);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
    }
    else
    {
        qDebug() << "连接本地服务器失败" << gSocket->error() << gSocket->errorString();
    }
}


void UnregisterClient()
{
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::UnregisterClientData(gClientId);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
        delete gSocket;
        gSocket = 0;
        gClientId = 0;
    }
}


void SendKeyUp(int keycode, uint flags)
{
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::KeyData(gClientId, keycode, false, flags);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
    }
}


void SendKeyDown(int keycode, uint flags)
{
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::KeyData(gClientId, keycode, true, flags);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
    }
}


void ChangePos(uint x, uint y)
{
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::PositionData(gClientId, x, y);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
    }
}
