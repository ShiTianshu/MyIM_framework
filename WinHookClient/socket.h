#ifndef SOCKET_H
#define SOCKET_H

#include "../MyBase/global.h"

bool SendKeyDown(int keycode, uint flags);
bool SendKeyUp(int keycode, uint flags);
void RegisterClient();
void UnregisterClient();
void ChangePos(uint x, uint y);


#endif // SOCKET_H
