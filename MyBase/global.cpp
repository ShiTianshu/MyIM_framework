#include "global.h"

#include <QProcess>
#include <QTextCodec>
#include <QJsonObject>
#include <QJsonDocument>

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

QString KeyData(qint64 id, uint keycode, bool press,
                bool lctrl, bool rctrl, bool lshift, bool rshift,
                bool lmenu, bool rmenu, bool lwin, bool rwin)
{
    int flags = 0;
    if (lctrl) flags |= LCONTROL;
    if (rctrl) flags |= RCONTROL;
    if (lshift) flags |= LSHIFT;
    if (rshift) flags |= RSHIFT;
    if (lmenu) flags |= LMENU;
    if (rmenu) flags |= RMENU;
    if (lwin) flags |= LWIN;
    if (rwin) flags |= RWIN;
    if (press)
    {
        return QString("%1|KD%2%3").arg(QString::number(id, 36))
                .arg(keycode & 0xFF,2,16,QLatin1Char('0'))
                .arg(flags & 0xFF,2,16,QLatin1Char('0'));
    }
    else
    {
        return QString("%1|KU%2%3").arg(QString::number(id, 36))
                .arg(keycode & 0xFF,2,16,QLatin1Char('0'))
                .arg(flags & 0xFF,2,16,QLatin1Char('0'));
    }
}

QString KeyData(qint64 id, uint keycode, bool press, int flags)
{
    if (press)
    {
        return QString("%1|KD%2%3").arg(QString::number(id, 36))
                .arg(keycode & 0xFF,2,16,QLatin1Char('0'))
                .arg(flags & 0xFF,2,16,QLatin1Char('0'));
    }
    else
    {
        return QString("%1|KU%2%3").arg(QString::number(id, 36))
                .arg(keycode & 0xFF,2,16,QLatin1Char('0'))
                .arg(flags & 0xFF,2,16,QLatin1Char('0'));
    }
}

QString RegisterClientData(qint64 id)
{
    return QString("%1|RC").arg(QString::number(id, 36));
}

QString UnregisterClientData(qint64 id)
{
    return QString("%1|UC").arg(QString::number(id, 36));
}

QString ChangeClientData(qint64 id)
{
    return QString("%1|CC").arg(QString::number(id, 36));
}

QString ResponseData(bool accepted, QString commitString, QString editText)
{
    return QString("%1||%2||%3").arg(accepted?1:0).arg(commitString).arg(editText);
}

void ParseResponseData(QString response, IMServerResponse &imres)
{
    QStringList list = response.split("||");
    imres.accepted = list.at(0).toInt() ? true : false;
    imres.commitString = list.at(1);
    imres.editText = list.at(2);
}

QString PositionData(qint64 id, int x, int y)
{
    return QString("%1|%2,%3").arg(QString::number(id, 36)).arg(x).arg(y);
}



}
