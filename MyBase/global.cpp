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

QDataStream &operator<<(QDataStream &out, const SrcEle &obj) {
    out << obj.id << obj.key << obj.value << obj.ext;
    return out;
}

QDataStream &operator>>(QDataStream &in, SrcEle &obj) {
    in >> obj.id >> obj.key >> obj.value >> obj.ext;
    return in;
}

QDebug &operator<<(QDebug &out, const SrcEle &obj) {
    out <<obj.id << obj.key << obj.value;
    return out;
}

bool SrcLessThan(const SrcEle &src1, const SrcEle &src2)
{
    return src1.key < src2.key;
}

}
