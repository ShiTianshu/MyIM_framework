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
#define LCONTROL    1
#define RCONTROL    2
#define LSHIFT      4
#define RSHIFT      8
#define LMENU       16
#define RMENU       32
#define LWIN        64
#define RWIN        128

namespace Global {

// 数据源的基本数据结构。
class SrcEle
{
public:
    uint id;
    QString key;
    QString value;
    int ext;                // 用作频率或者其它标识，或是其它数据的id等。
    // Override operator << and >>.
    friend QDataStream &operator<<(QDataStream &out, const SrcEle &obj);
    friend QDataStream &operator>>(QDataStream &in, SrcEle &obj);

    friend QDebug &operator<<(QDebug &out, const SrcEle &obj);
};

const QString & GetMyPath();
void SetSettingsCodec(QSettings* settings, QByteArray codec="UTF-8");
bool SrcLessThan(const SrcEle &src1, const SrcEle &src2);

// 通信数据生成。
/**
 * @brief KeyData   生成按键的通信字符串。
 *                  功能键的标志位，在其自身按下时，可任意传入。
 * @param id
 * @param keycode   键值
 * @param press     是否是按下
 */
QString KeyData(qint64 id, uint keycode, bool press,
                bool lctrl, bool rctrl, bool lshift, bool rshift,
                bool lmenu, bool rmenu, bool lwin, bool rwin);
QString KeyData(qint64 id, uint keycode, bool press, int flags);
QString PositionData(qint64, int x, int y);
QString RegisterClientData(qint64 id);
QString UnregisterClientData(qint64 id);
QString ChangeClientData(qint64 id);

/**
 * @brief ResponseData  服务器响应
 * @param accepted      是否处理该按键。
 * @param commitString  上屏的字符串
 * @param text          嵌入的编码
 */
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
