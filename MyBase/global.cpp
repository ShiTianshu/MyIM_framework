#include "global.h"

#include <QProcess>
#include <QTextCodec>

namespace Global {

QString myPath;

// 获得输入法的程序路径。
// WIN下为环境变量MYIM_HOME （待定）
const QString & GetMyPath()
{
    if (myPath.isEmpty())
    {
        QStringList envs = QProcess::systemEnvironment();
        foreach (QString str, envs)
        {
            if (str.startsWith("MYIM_HOME="))
            {
                myPath = str.split("=")[1];
                break;
            }
        }
        if (myPath.isEmpty())
        {
            throw QString("没有MYIM_HOME环境变量");
        }
    }
    return myPath;
}

void SetSettingsCodec(QSettings *settings, QByteArray codec)
{
    settings->setIniCodec(QTextCodec::codecForName(codec));
}

}
