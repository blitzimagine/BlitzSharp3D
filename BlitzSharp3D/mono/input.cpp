#include "monoutil.h"
#include "../bbruntime/bbinput.h"

PUBLIC_METHOD int KeyHit(int key)
{
	return bbKeyHit(key) != 0;
}

PUBLIC_METHOD int KeyDown(int key)
{
	return bbKeyDown(key) != 0;
}

PUBLIC_METHOD int GetKey()
{
	return bbGetKey();
}

PUBLIC_METHOD int WaitKey()
{
	return bbWaitKey();
}

PUBLIC_METHOD void FlushKeys()
{
	return bbFlushKeys();
}

PUBLIC_METHOD int MouseDown(int button)
{
	return bbMouseDown(button) != 0;
}

PUBLIC_METHOD int MouseHit(int button)
{
	return bbMouseHit(button) != 0;
}

PUBLIC_METHOD int GetMouse()
{
	return bbGetMouse();
}

PUBLIC_METHOD int WaitMouse()
{
	return bbWaitMouse();
}

// Matt: Why exactly is there an extra copy of this?
PUBLIC_METHOD int MouseWait()
{
	return bbWaitMouse();
}

PUBLIC_METHOD int MouseX()
{
	return bbMouseX();
}

PUBLIC_METHOD int MouseY()
{
	return bbMouseY();
}

PUBLIC_METHOD int MouseZ()
{
	return bbMouseZ();
}

PUBLIC_METHOD int MouseXSpeed()
{
	return bbMouseXSpeed();
}

PUBLIC_METHOD int MouseYSpeed()
{
	return bbMouseYSpeed();
}

PUBLIC_METHOD int MouseZSpeed()
{
	return bbMouseZSpeed();
}

PUBLIC_METHOD void FlushMouse()
{
	bbFlushMouse();
}

PUBLIC_METHOD void MoveMouse(int x, int y)
{
	bbMoveMouse(x, y);
}

PUBLIC_METHOD int JoyType(int port)
{
	return bbJoyType(port);
}

PUBLIC_METHOD int JoyDown(int button, int port)
{
	return bbJoyDown(button, port) != 0;
}

PUBLIC_METHOD int JoyHit(int button, int port)
{
	return bbJoyHit(button, port) != 0;
}

PUBLIC_METHOD int GetJoy(int port)
{
	return bbGetJoy(port);
}

PUBLIC_METHOD int WaitJoy(int port)
{
	return bbWaitJoy(port);
}

// Matt: Again, why is there an extra copy of this?
PUBLIC_METHOD int JoyWait(int port)
{
	return bbWaitJoy(port);
}

PUBLIC_METHOD float JoyX(int port)
{
	return bbJoyX(port);
}

PUBLIC_METHOD float JoyY(int port)
{
	return bbJoyY(port);
}

PUBLIC_METHOD float JoyZ(int port)
{
	return bbJoyZ(port);
}

PUBLIC_METHOD float JoyU(int port)
{
	return bbJoyU(port);
}

PUBLIC_METHOD float JoyV(int port)
{
	return bbJoyV(port);
}

PUBLIC_METHOD float JoyPitch(int port)
{
	return bbJoyPitch(port);
}

PUBLIC_METHOD float JoyYaw(int port)
{
	return bbJoyYaw(port);
}

PUBLIC_METHOD float JoyRoll(int port)
{
	return bbJoyRoll(port);
}

PUBLIC_METHOD int JoyHat(int port)
{
	return bbJoyHat(port);
}

PUBLIC_METHOD int JoyXDir(int port)
{
	return bbJoyXDir(port);
}

PUBLIC_METHOD int JoyYDir(int port)
{
	return bbJoyYDir(port);
}

PUBLIC_METHOD int JoyZDir(int port)
{
	return bbJoyZDir(port);
}

PUBLIC_METHOD int JoyUDir(int port)
{
	return bbJoyUDir(port);
}

PUBLIC_METHOD int JoyVDir(int port)
{
	return bbJoyVDir(port);
}

PUBLIC_METHOD int JoyPitchDir(int port)
{
	return bbJoyPitchDir(port);
}

PUBLIC_METHOD int JoyYawDir(int port)
{
	return bbJoyYawDir(port);
}

PUBLIC_METHOD int JoyRollDir(int port)
{
	return bbJoyRollDir(port);
}

PUBLIC_METHOD void FlushJoy()
{
	bbFlushJoy();
}

PUBLIC_METHOD void EnableDirectInput(int enable)
{
	bbEnableDirectInput(enable ? 1 : 0);
}

PUBLIC_METHOD int DirectInputEnabled()
{
	return bbDirectInputEnabled() != 0;
}