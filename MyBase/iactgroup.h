#ifndef IACTGROUP_H
#define IACTGROUP_H

#include "iact.h"

/**
 * @brief The IAct class
 * 输入法行为组接口。
 * 任何一个输入法模块，都可以通过：
 * emit action(actId) actId格式为{行为组ID#参数}
 * 来触发行为组。一个组可以跟据参数进行下级行为的分发，
 * 或是完成一连串的调用，或是实现一个需要额外参数的复杂行为。
 * 触发的行为组会执行executeGroup方法，参数触发参数和当前的输入法上下文。
 * 从上下文中获得需要的数据，并将结果存入到上下文当中。
 * 继承需要实现executeGroup, initialize
 */
class IActGroup: public IAct
{
public:
    IActGroup(QString id);
    virtual ~IActGroup();
    virtual void executeGroup(QString arg, InputContext* pic) = 0;
};

#endif // IACTGROUP_H
