#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include <QLocalServer>
#include <QLocalSocket>
#include "../MyCore/mycore.h"

class MyServer: public QObject
{

    Q_OBJECT
public:
    MyServer();
    ~MyServer();
    void initialize();

private:
    QLocalServer *server;
    MyCore *core;
    void _initCore();
    void _initSocket();
    bool _isServerRun();

    QString _dispatch(const QString &data);

private slots:
    void newConnection();
    void readyRead();
    void disconnected();
};

#endif // MYSERVER_H
