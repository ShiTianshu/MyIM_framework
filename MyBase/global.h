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

const QString & GetMyPath();
void SetSettingsCodec(QSettings* settings, QByteArray codec="UTF-8");

// 数据源的基本数据结构。
typedef struct TagSrcElement
{
    uint id;
    QString key;
    QString value;
    QVariant extInfo;
}SrcEle;

}
#endif // GLOBAL_H
