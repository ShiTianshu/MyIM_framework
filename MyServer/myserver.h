//    Server 通信标准。
//    键盘按下事件：{id}|KD{flags}
//    键盘抬起事件：{id}|KU{flags}
//    注册上下文：{id}|RC
//    注销上下文：{id}|UC
//    切换上下文：{id}|CC
//    光标位置：{id}|PS{x},{y}

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include <QLocalServer>
#include <QLocalSocket>

class MyServer: public QObject
{

    Q_OBJECT
public:
    MyServer();
    ~MyServer();
    void initialize();

private:
    QLocalServer *server;
    void _initCore();
    void _initSocket();
    bool _isServerRun();


private slots:
    void newConnection();
    void readyRead();
};

#endif // MYSERVER_H
