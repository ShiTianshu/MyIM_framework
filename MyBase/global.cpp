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

QDataStream &operator <<(QDataStream &out, const SrcItem &item)
{
    out << item.id << item.key << item.value << item.ext;
    return out;
}

QDataStream &operator >>(QDataStream &in, SrcItem &item)
{
    in >> item.id >> item.key >> item.value >> item.ext;
    return in;
}

QDataStream &operator>>(QDataStream &out, const SrcItem * const item)
{
    out << *item;
    return out;
}

QDataStream &operator<<(QDataStream &in, SrcItem * const item)
{
    in >> *item;
    return in;
}

QDebug &operator<<(QDebug &out, const SrcItem &item)
{
    out << item.id << item.key << item.value << item.ext;
    return out;
}

/**
 * @brief KeyData   生成按键的通信字符串。
 *                  功能键的标志位，在其自身按下时，可任意传入。
 * @param id
 * @param keycode   键值
 * @param press     是否是按下
 */
QString KeyData(qint64 id, uint keycode, bool press,
                bool lctrl, bool rctrl, bool lshift, bool rshift,
                bool lmenu, bool rmenu, bool lwin, bool rwin)
{
    int flags = 0;
    if (lctrl) flags |= LCONTROL_FLAG;
    if (rctrl) flags |= RCONTROL_FLAG;
    if (lshift) flags |= LSHIFT_FLAG;
    if (rshift) flags |= RSHIFT_FLAG;
    if (lmenu) flags |= LMENU_FLAG;
    if (rmenu) flags |= RMENU_FLAG;
    if (lwin) flags |= LSPECIAL_FLAG;
    if (rwin) flags |= RSPECIAL_FLAG;
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

/**
 * @brief ResponseData  服务器响应
 * @param accepted      是否处理该按键。
 * @param commitString  上屏的字符串
 * @param text          嵌入的编码
 */
QString ResponseData(bool accepted, QString commitString, QString editText)
{
    return QString("%1||%2||%3").arg(accepted?1:0).arg(commitString).arg(editText);
}

void ParseResponseData(QString response, IMServerResponse &imres)
{
    if (response == "N")
    {
        imres.accepted = false;
        imres.commitString = "";
        imres.editText = "";
    }
    else
    {
        QStringList list = response.split("||");
        imres.accepted = list.at(0).toInt() ? true : false;
        imres.commitString = list.at(1);
        imres.editText = list.at(2);
    }
}

QString PositionData(qint64 id, int x, int y)
{
    return QString("%1|PS%2,%3").arg(QString::number(id, 36)).arg(x).arg(y);
}

void SrcCursor::setPageSize(int pageSize)
{
    this->pageSize = pageSize;
}

bool SrcCursor::hasNext()
{
    return this->_hasNext;
}

}
