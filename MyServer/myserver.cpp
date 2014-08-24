#include "myserver.h"
#include "../MyBase/global.h"
#include "../MyCore/mycore.h"

#include <QLibrary>

MyServer::MyServer()
{

}

MyServer::~MyServer()
{
    qDebug() << "析构MyServer";
    delete this->server;
}

void MyServer::initialize()
{
    this->_initCore();
    this->_initSocket();
}

// 创建输入法核心。
void MyServer::_initCore()
{
    try
    {
        QString corePath = QString("%1/mod/MyCore").arg(Global::GetMyPath());
        QLibrary coreLib(corePath);
        if (!coreLib.load())
        {
            throw QString("无法找到核心，路径%1").arg(corePath);
        }
        GetCoreInstance gci = (GetCoreInstance)coreLib.resolve("GetInstance");
        if (!gci)
        {
            throw QString("核心模块缺少GetInstance函数");
        }
        MyCore* pc = gci();
        if (!pc)
        {
            throw QString("无法创建核心实例");
        }
        pc->initialize();
    }
    catch(QString exception)
    {
        throw QString("核心初始化失败，原因：\n\t%1\n").arg(exception);
    }
}

// 创建LocalSocket
void MyServer::_initSocket()
{
    qDebug() << "创建server";
    if (this->_isServerRun())
    {
        throw QString("服务器已经在运行了");
    }
    this->server = new QLocalServer;
    qDebug() << this->server->listen(SERVER_NAME);
}

bool MyServer::_isServerRun()
{
    // 用一个localsocket去连一下,如果能连上就说明
    // 有一个在运行了
    QLocalSocket ls;
    ls.connectToServer(SERVER_NAME);
    if (ls.waitForConnected(1000)){
        // 说明已经在运行了
        ls.disconnectFromServer();
        ls.close();
        return true;
    }
    return false;
}

void MyServer::newConnection()
{
    QLocalSocket *newsocket = this->server->nextPendingConnection();
    connect(newsocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyServer::readyRead()
{
    QLocalSocket* socket = static_cast< QLocalSocket* >(sender());
    if (!socket)
    {
        throw QString("读取数据时找不到socket");
    }
    QTextStream in(socket);
    QString msg;
    msg = in.readAll();
    qDebug() << msg;
}



