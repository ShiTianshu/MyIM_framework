#include "myserver.h"
#include "../MyBase/global.h"
#include "../MyCore/mycore.h"

#include <QLibrary>

MyServer::MyServer()
{

}

MyServer::~MyServer()
{

}

void MyServer::initialize()
{
    // 创建输入法核心。
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
