#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QDebug>
#include <QSettings>

#define PROC_MOD    'P'
#define ACT_MOD     'A'
#define SRC_MOD     'S'
#define EXT_MOD     'E'
#define UNKNOWN_MOD 'U'

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

}
#endif // GLOBAL_H
