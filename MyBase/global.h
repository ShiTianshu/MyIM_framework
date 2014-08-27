#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QDebug>
#include <QSettings>

#define SERVER_NAME "myim_server"

// 模块类型
#define PROC_MOD    'P'
#define ACT_MOD     'A'
#define SRC_MOD     'S'
#define EXT_MOD     'E'
#define UNKNOWN_MOD 'U'

// 功能键的标志位。
#define LCONTROL_FLAG    1
#define RCONTROL_FLAG    2
#define LSHIFT_FLAG      4
#define RSHIFT_FLAG      8
#define LMENU_FLAG       16
#define RMENU_FLAG       32
#define LSPECIAL_FLAG    64
#define RSPECIAL_FLAG    128
#define CONTROL_FLAG     LCONTROL_FLAG | RCONTROL_FLAG
#define SHIFT_FLAG       LSHIFT_FLAG   | RSHIFT_FLAG
#define MENU_FLAG        LMENU_FLAG    | RMENU_FLAG
#define SPECIAL_FLAG     LSPECIAL_FLAG | RSPECIAL_FLAG

namespace Global {

// 数据源的基本数据结构。
class SrcEle
{
public:
    uint id;
    QString key;
    QString value;
    int ext;                // 用作频率或者其它标识，或是其它数据的id等。待定
    // Override operator << and >>.
    friend QDataStream &operator<<(QDataStream &out, const SrcEle &obj);
    friend QDataStream &operator>>(QDataStream &in, SrcEle &obj);

    friend QDebug &operator<<(QDebug &out, const SrcEle &obj);
};

const QString & GetMyPath();
void SetSettingsCodec(QSettings* settings, QByteArray codec="UTF-8");
bool SrcLessThan(const SrcEle &src1, const SrcEle &src2);

// 通信数据生成。
QString KeyData(qint64 id, uint keycode, bool press,
                bool lctrl, bool rctrl, bool lshift, bool rshift,
                bool lmenu, bool rmenu, bool lwin, bool rwin);
QString KeyData(qint64 id, uint keycode, bool press, int flags);
QString PositionData(qint64, int x, int y);
QString RegisterClientData(qint64 id);
QString UnregisterClientData(qint64 id);
QString ChangeClientData(qint64 id);
QString ResponseData(bool accepted, QString commitString, QString editText);

// 输入法server返回响应。
typedef struct TagIMServerResponse
{
    bool accepted;
    QString commitString;
    QString editText;
}IMServerResponse;
void ParseResponseData(QString response, IMServerResponse &imres);

}
#endif // GLOBAL_H
