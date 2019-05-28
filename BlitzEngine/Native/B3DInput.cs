using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using BlitzEngine.Enums;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// -----
		// Input
		// -----

		[DllImport(B3DDllLink)]
		public static extern bool KeyHit(Keys key);

		[DllImport(B3DDllLink)]
		public static extern bool KeyDown(Keys key);

		[DllImport(B3DDllLink)]
		public static extern int GetKey();

		[DllImport(B3DDllLink)]
		public static extern Keys WaitKey();

		[DllImport(B3DDllLink)]
		public static extern void FlushKeys();

		[DllImport(B3DDllLink)]
		public static extern bool MouseDown(int button);

		[DllImport(B3DDllLink)]
		public static extern bool MouseHit(int button);

		[DllImport(B3DDllLink)]
		public static extern int GetMouse();

		[DllImport(B3DDllLink)]
		public static extern int WaitMouse();

		[DllImport(B3DDllLink)]
		public static extern int MouseWait();

		[DllImport(B3DDllLink)]
		public static extern int MouseX();

		[DllImport(B3DDllLink)]
		public static extern int MouseY();

		[DllImport(B3DDllLink)]
		public static extern int MouseZ();

		[DllImport(B3DDllLink)]
		public static extern int MouseXSpeed();

		[DllImport(B3DDllLink)]
		public static extern int MouseYSpeed();

		[DllImport(B3DDllLink)]
		public static extern int MouseZSpeed();

		[DllImport(B3DDllLink)]
		public static extern void FlushMouse();

		[DllImport(B3DDllLink)]
		public static extern void MoveMouse(int x, int y);

		[DllImport(B3DDllLink)]
		public static extern int JoyType(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern bool JoyDown(int button, int port = 0);

		[DllImport(B3DDllLink)]
		public static extern bool JoyHit(int button, int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int GetJoy(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int WaitJoy(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyWait(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyX(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyY(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyZ(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyU(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyV(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyPitch(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyYaw(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern float JoyRoll(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyHat(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyXDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyYDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyZDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyUDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyVDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyPitchDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyYawDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern int JoyRollDir(int port = 0);

		[DllImport(B3DDllLink)]
		public static extern void FlushJoy();

		[DllImport(B3DDllLink)]
		public static extern void EnableDirectInput(bool enable);

		[DllImport(B3DDllLink)]
		public static extern bool DirectInputEnabled();
	}
}
