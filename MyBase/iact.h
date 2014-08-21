#ifndef IACT_H
#define IACT_H

#include "imod.h"
#include "inputcontext.h"

/** --------------------------------------------------------------------
 * @brief The IAct class
 * 输入法行为接口。
 * 任何一个输入法模块，都可以通过：
 * emit action(actId)
 * 来触发行为。
 * 触发的行为会执行execute方法，参数为当前的输入法上下文。
 * 从上下文中获得需要的数据，并将结果存入到上下文当中。
 * 继承需要实现execute, initialize
 * ---------------------------------------------------------------------
 */
class IAct:
        public IMod
{
public:
    IAct(QString id);
    virtual ~IAct() = 0;
    virtual void execute(InputContext* pic) = 0;
};

#endif // IACT_H
