#include "socket.h"
#include "sender.h"
#include "caret.h"
#include <QLocalSocket>
#include <QDateTime>
#include <QTextStream>

QLocalSocket* gSocket;
qint64 gClientId = 0;

void _SendPos()
{
    if (gSocket && gSocket->isWritable())
    {
        POINT pos;
        FillPos(pos);
        QString data = Global::PositionData(gClientId, pos.x, pos.y);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
        if (gSocket->waitForReadyRead())
        {
            QTextStream in(gSocket);
            in.readAll();
        }
    }
}

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
        if (gSocket->waitForReadyRead())
        {
            QTextStream in(gSocket);
            in.readAll();
        }
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


bool SendKeyUp(int keycode, uint flags)
{
    _SendPos();
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::KeyData(gClientId, keycode, false, flags);
        qDebug() << data;
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
        if (gSocket->waitForReadyRead())
        {
            QTextStream in(gSocket);
            QString response = in.readAll();
            Global::IMServerResponse imres;
            Global::ParseResponseData(response, imres);
            if (!imres.commitString.isEmpty())
            {
                qDebug() << imres.commitString;
                SendString(imres.commitString);
            }
            return imres.accepted;
        }
    }
    _SendPos();
    return false;
}


bool SendKeyDown(int keycode, uint flags)
{
    _SendPos();
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::KeyData(gClientId, keycode, true, flags);
        qDebug() << data;
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
        if (gSocket->waitForReadyRead())
        {
            QTextStream in(gSocket);
            QString response = in.readAll();
            Global::IMServerResponse imres;
            Global::ParseResponseData(response, imres);
            if (!imres.commitString.isEmpty())
            {
                qDebug() << imres.commitString;
                SendString(imres.commitString);
            }
            return imres.accepted;
        }
    }
    _SendPos();
    return false;
}


void ChangePos(uint x, uint y)
{
    if (gSocket && gSocket->isWritable())
    {
        QString data = Global::PositionData(gClientId, x, y);
        gSocket->write(data.toLocal8Bit());
        gSocket->flush();
        if (gSocket->waitForReadyRead())
        {
            QTextStream in(gSocket);
            in.readAll();
        }
    }
}
