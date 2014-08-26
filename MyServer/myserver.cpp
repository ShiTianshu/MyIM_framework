#include "myserver.h"
#include "../MyBase/global.h"


#include <QLibrary>
#include <QMessageBox>

MyServer::MyServer()
{

}

MyServer::~MyServer()
{
    qDebug() << "析构MyServer";
    delete this->core;
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
        this->core = gci();
        if (!core)
        {
            throw QString("无法创建核心实例");
        }
        core->initialize();
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
    if (!this->server->listen(SERVER_NAME))
    {
        throw QString("服务器无法侦听");
    }
    connect(this->server, SIGNAL(newConnection()), this, SLOT(newConnection()));
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

QString MyServer::_dispatch(const QString &data)
{
    qDebug() << QString("dispatch: %1").arg(data);
    QString response = "N";
    QStringList list = data.split("|");
    bool ok;
    qint64 id = list.at(0).toLongLong(&ok, 36);
    if (!ok)
    {
        throw QString("无法从%1获得正确的id").arg(data);
    }
    QString params = list.at(1);
    QStringRef event = params.leftRef(2);
    if (event == "RC")
    {
        // 注册
        this->core->registerCtx(id);
    }
    else if (event == "UC")
    {
        // 注销
        this->core->unregisterCtx(id);
    }
    else if (event == "CC")
    {
        // 切换
    }
    else if (event == "PS")
    {
        // 位置
    }
    else if (event == "KD")
    {
        // 按键按下
        uint keycode = list.at(1).midRef(2, 2).toInt(&ok, 16);
        if (!ok)
        {
            throw QString ("消息%1传送了无效的键值").arg(data);
        }
        response = this->core->onKeyDown(keycode);
    }
    else if (event == "KU")
    {
        // 按键抬起
        uint keycode = list.at(1).midRef(2, 2).toInt(&ok, 16);
        if (!ok)
        {
            throw QString ("消息%1传送了无效的键值").arg(data);
        }
        response = this->core->onKeyUp(keycode);
    }
    else
    {
        throw QString ("无法识别的消息%1").arg(data);
    }
    return response;
}

void MyServer::newConnection()
{
    qDebug() << "client连接";
    QLocalSocket *socket = this->server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void MyServer::readyRead()
{
    QLocalSocket *socket = static_cast< QLocalSocket* >(sender());
    QTextStream in(socket);
    QString data;
    data = in.readAll();
    try
    {
        QString response = this->_dispatch(data);
        if (socket->isWritable())
        {
            socket->write(response.toLocal8Bit());
            socket->flush();
        }
    }
    catch(QString exception)
    {
        QMessageBox::critical(0, "出错了", exception);
    }
}

void MyServer::disconnected()
{
    qDebug() << "断开当前连接";
    QLocalSocket *socket = static_cast< QLocalSocket* >(sender());
    socket->close();
}



