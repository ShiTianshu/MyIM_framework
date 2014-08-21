#ifndef IEXT_H
#define IEXT_H

#include "imod.h"

/** --------------------------------------------------------------------
 * @brief The IExt class
 * 扩展模块
 * ---------------------------------------------------------------------
 */
class IExt: public IMod
{
public:
    IExt(QString id);
    ~IExt();
};

#endif // IEXT_H
