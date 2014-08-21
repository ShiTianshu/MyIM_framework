#ifndef IPROC_H
#define IPROC_H

#include "imod.h"
#include "inputcontext.h"

/** --------------------------------------------------------------------
 * @brief The IProc class
 * 输入法处理器接口
 * 实现并在engine配置文件添加的处理器队列，会被输入法的事件按顺序触发。
 * 每一个处理器调用execute方法，参数为当前的输入法上下文。
 * 从上下文中获得需要的数据，并将结果存入到上下文当中。
 * 继承需要实现execute, initialize
 * ---------------------------------------------------------------------
 */
class IProc:
        public IMod
{
public:
    IProc(QString id);
    virtual ~IProc();
    virtual void execute(InputContext* pic)=0;
};

#endif // IPROC_H
