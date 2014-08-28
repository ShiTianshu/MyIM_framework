#ifndef COMM_H
#define COMM_H

#include <QString>





namespace Comm{

// 通信的类型。
const int KEYDOWN       = 1;
const int KEYUP         = 2;
const int REGISTER      = 4;
const int UNREGISTER    = 8;
const int CARETPOS      = 16;
const int FOCUSIN       = 32;
const int FOCUSOUT      = 64;
const int RESPONSE      = 128;

// 客户端请求的结构体。
typedef struct TagMyMsg
{


}MyMsg;

}

#endif // COMM_H
