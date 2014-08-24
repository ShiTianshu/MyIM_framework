#ifndef SOCKET_H
#define SOCKET_H

#include "../MyBase/global.h"

void SendKeyDown(char keycode, uint flags);
void SendKeyUp(char keycode, uint flags);
void RegisterClient();
void UnregisterClient();
void ChangePos(uint x, uint y);


#endif // SOCKET_H
