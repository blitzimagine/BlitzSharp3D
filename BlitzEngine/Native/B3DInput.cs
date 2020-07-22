using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Microsoft.Xna.Framework.Input;
using XKeys = Microsoft.Xna.Framework.Input.Keys;
using Keys = BlitzEngine.Enums.Keys;
using System.Threading;
using Microsoft.Xna.Framework;

namespace BlitzEngine
{
	public static class B3DInput
	{
		public static readonly B3DKeyboard Keyboard = new B3DKeyboard();
		public static readonly B3DMouse Mouse = new B3DMouse();
		//public static readonly List<B3DJoystick> Joysticks = new List<B3DJoystick>();

		internal static void Update()
		{
			Keyboard.Update();
			Mouse.Update();
			//foreach(B3DJoystick joystick in Joysticks){joystick.Update();}
		}

		public abstract class B3DDevice
		{
			protected const int QUE_SIZE = 32;

			protected readonly int[] hit_count = new int[256];
			protected readonly bool[] down_state = new bool[256];
			//protected readonly float[] axis_states = new float[32];

			protected readonly Queue<int> que = new Queue<int>(QUE_SIZE);
			
			public void Reset()
			{
				Array.Clear(hit_count, 0, hit_count.Length);
				Array.Clear(down_state, 0, down_state.Length);
				que.Clear();
			}

			protected void SetKeysDown<T>(T keys) where T:IEnumerable<int>
			{
				bool[] newDownStates = ToDownStateArray(keys);
				for(int key=0; key<newDownStates.Length; key++)
				{
					SetDownState(key, newDownStates[key]);
				}
			}

			protected void SetDownState(int key, bool down)
			{
				if(down == down_state[key]) return;

				if(down)
				{
					down_state[key] = true;
					hit_count[key]++;
					if(que.Count < QUE_SIZE)
					{
						que.Enqueue(key);
					}
				}
				else
				{
					down_state[key] = false;
				}
			}

			protected bool[] ToDownStateArray<T>(T keys) where T:IEnumerable<int>
			{
				bool[] down_state = new bool[256];
				foreach(int key in keys)
				{
					down_state[key] = true;
				}
				return down_state;
			}

			public void Flush()
			{
				Array.Clear(hit_count, 0, hit_count.Length);
				que.Clear();
			}

			public bool KeyDown(int key) => down_state[key];

			public int KeyHit(int key)
			{
				int n = hit_count[key];
				hit_count[key] -= n;
				return n;
			}

			public int GetKey() => que.Count>0 ? que.Dequeue() : 0;

			//public float GetAxisState(int axis) => axis_states[axis];

			internal int WaitKey()
			{
				while(true)
				{
					int key = GetKey();
					if(key != 0)
					{
						return key;
					}
					Thread.Sleep(20);
				}
			}

			public abstract void Update();
		}

		public sealed class B3DKeyboard:B3DDevice
		{
			public override void Update()
			{
				IEnumerable<int> bbKeysDown = Microsoft.Xna.Framework.Input.Keyboard.GetState().GetPressedKeys().Select(k=>(int)KeyMap(k));
				SetKeysDown(bbKeysDown);
			}

			private static Keys KeyMap(XKeys key)
			{
				switch(key)
				{
					case XKeys.Escape: return Keys.ESCAPE;
					case XKeys.D1: return Keys.ONE;
					case XKeys.D2: return Keys.TWO;
					case XKeys.D3: return Keys.THREE;
					case XKeys.D4: return Keys.FOUR;
					case XKeys.D5: return Keys.FIVE;
					case XKeys.D6: return Keys.SIX;
					case XKeys.D7: return Keys.SEVEN;
					case XKeys.D8: return Keys.EIGHT;
					case XKeys.D9: return Keys.NINE;
					case XKeys.D0: return Keys.ZERO;
					case XKeys.OemMinus: return Keys.MINUS;
					case XKeys.OemPlus: return Keys.EQUALS;
					case XKeys.Back: return Keys.BACKSPACE;
					case XKeys.Tab: return Keys.TAB;
					case XKeys.Q: return Keys.Q;
					case XKeys.W: return Keys.W;
					case XKeys.E: return Keys.E;
					case XKeys.R: return Keys.R;
					case XKeys.T: return Keys.T;
					case XKeys.Y: return Keys.Y;
					case XKeys.U: return Keys.U;
					case XKeys.I: return Keys.I;
					case XKeys.O: return Keys.O;
					case XKeys.P: return Keys.P;
					case XKeys.OemOpenBrackets: return Keys.LBRACKET;
					case XKeys.OemCloseBrackets: return Keys.RBRACKET;
					case XKeys.Enter: return Keys.ENTER;
					case XKeys.LeftControl: return Keys.LCTRL;
					case XKeys.A: return Keys.A;
					case XKeys.S: return Keys.S;
					case XKeys.D: return Keys.D;
					case XKeys.F: return Keys.F;
					case XKeys.G: return Keys.G;
					case XKeys.H: return Keys.H;
					case XKeys.J: return Keys.J;
					case XKeys.K: return Keys.K;
					case XKeys.L: return Keys.L;
					case XKeys.OemSemicolon: return Keys.SEMI_COLON;
					case XKeys.OemQuotes: return Keys.APOSTROPHE;
					case XKeys.OemTilde: return Keys.GRAVE;
					case XKeys.LeftShift: return Keys.LSHIFT;
					case XKeys.OemBackslash: return Keys.BACKSLASH;
					case XKeys.Z: return Keys.Z;
					case XKeys.X: return Keys.X;
					case XKeys.C: return Keys.C;
					case XKeys.V: return Keys.V;
					case XKeys.B: return Keys.B;
					case XKeys.N: return Keys.N;
					case XKeys.M: return Keys.M;
					case XKeys.OemComma: return Keys.COMMA;
					case XKeys.OemPeriod: return Keys.PERIOD;
					case XKeys.OemQuestion: return Keys.SLASH;
					case XKeys.RightShift: return Keys.RSHIFT;
					case XKeys.Multiply: return Keys.NUMPAD_MULTIPLY;
					case XKeys.LeftAlt: return Keys.LALT;
					case XKeys.Space: return Keys.SPACE;
					case XKeys.CapsLock: return Keys.CAPSLOCK;
					case XKeys.F1: return Keys.F1;
					case XKeys.F2: return Keys.F2;
					case XKeys.F3: return Keys.F3;
					case XKeys.F4: return Keys.F4;
					case XKeys.F5: return Keys.F5;
					case XKeys.F6: return Keys.F6;
					case XKeys.F7: return Keys.F7;
					case XKeys.F8: return Keys.F8;
					case XKeys.F9: return Keys.F9;
					case XKeys.F10: return Keys.F10;
					case XKeys.NumLock: return Keys.NUMLOCK;
					case XKeys.Scroll: return Keys.SCROLL_LOCK;
					case XKeys.NumPad7: return Keys.NUMPAD_7;
					case XKeys.NumPad8: return Keys.NUMPAD_8;
					case XKeys.NumPad9: return Keys.NUMPAD_9;
					case XKeys.Subtract: return Keys.NUMPAD_MINUS;
					case XKeys.NumPad4: return Keys.NUMPAD_4;
					case XKeys.NumPad5: return Keys.NUMPAD_5;
					case XKeys.NumPad6: return Keys.NUMPAD_6;
					case XKeys.Add: return Keys.NUMPAD_ADD;
					case XKeys.NumPad1: return Keys.NUMPAD_1;
					case XKeys.NumPad2: return Keys.NUMPAD_2;
					case XKeys.NumPad3: return Keys.NUMPAD_3;
					case XKeys.NumPad0: return Keys.NUMPAD_0;

					//case XKeys.OemPeriod: return Keys.NUMPAD_DOT;

					//case XKeys.OEM_102: return Keys.OEM_102; // UK/Germany Keyboards
					case XKeys.F11: return Keys.F11;
					case XKeys.F12: return Keys.F12;
					case XKeys.F13: return Keys.F13;
					case XKeys.F14: return Keys.F14;
					case XKeys.F15: return Keys.F15;
					case XKeys.Kana: return Keys.KANA; // Japanese Keyboard
					//case XKeys.ABNT_C1: return Keys.ABNT_C1; // /? on Portugese (Brazilian) keyboards
					case XKeys.ImeConvert: return Keys.CONVERT; // Japanese Keyboard
					case XKeys.ImeNoConvert: return Keys.NOCONVERT; // Japanese Keyboard
					//case XKeys.YEN: return Keys.YEN; // Japanese Keyboard
					//case XKeys.ABNT_C2: return Keys.ABNT_C2; // Numpad . on Portugese (Brazilian) keyboards
					//case XKeys.NUMPAD_EQUALS: return Keys.NUMPAD_EQUALS; // = on numeric keypad (NEC PC98)
					case XKeys.MediaPreviousTrack: return Keys.PREVTRACK; // Previous Track (DIK_CIRCUMFLEX on Japanese keyboard)
					//case XKeys.AT: return Keys.AT; // (NEC PC98)
					//case XKeys.COLON: return Keys.COLON; // (NEC PC98)
					//case XKeys.UNDERLINE: return Keys.UNDERLINE; // (NEC PC98)
					case XKeys.Kanji: return Keys.KANJI; // Japanese Keyboard
					//case XKeys.STOP: return Keys.STOP; // (NEC PC98)
					//case XKeys.AX: return Keys.AX; // Japan AX
					//Unlabeled = 151, // (J3100)
					case XKeys.MediaNextTrack: return Keys.NEXT_TRACK;
					//case XKeys.Enter: return Keys.NUMPAD_ENTER;
					case XKeys.RightControl: return Keys.RCTRL;
					case XKeys.VolumeMute: return Keys.MUTE;
					//case XKeys.CALCULATOR: return Keys.CALCULATOR;
					case XKeys.MediaPlayPause: return Keys.PLAY_PAUSE;
					case XKeys.MediaStop: return Keys.MEDIA_STOP;
					case XKeys.VolumeDown: return Keys.VOLUME_DOWN;
					case XKeys.VolumeUp: return Keys.VOLUME_UP;
					case XKeys.BrowserHome: return Keys.WEB_HOME;
					//case XKeys.NUMPAD_COMMA: return Keys.NUMPAD_COMMA; // (NEX PC98)
					case XKeys.Divide: return Keys.NUMPAD_DIVIDE;
					//case XKeys.PrintScreen: return Keys.SYSREQ;
					case XKeys.RightAlt: return Keys.RALT;
					case XKeys.Pause: return Keys.PAUSE;
					case XKeys.Home: return Keys.HOME;
					case XKeys.Up: return Keys.UP; // Up Arrow
					case XKeys.PageUp: return Keys.PAGE_UP;
					case XKeys.Left: return Keys.LEFT; // Left Arrow
					case XKeys.Right: return Keys.RIGHT; // Right Arrow
					case XKeys.End: return Keys.END;
					case XKeys.Down: return Keys.DOWN; // Down Arrow
					//case XKeys.NEXT: return Keys.NEXT;
					case XKeys.Insert: return Keys.INSERT;
					case XKeys.Delete: return Keys.DELETE;
					case XKeys.LeftWindows: return Keys.LWIN;
					case XKeys.RightWindows: return Keys.RWIN;
					case XKeys.Apps: return Keys.APPS;
					//case XKeys.POWER: return Keys.POWER;
					case XKeys.Sleep: return Keys.SLEEP;
					//case XKeys.WAKE: return Keys.WAKE;
					case XKeys.BrowserSearch: return Keys.WEB_SEARCH;
					case XKeys.BrowserFavorites: return Keys.WEB_FAVORITES;
					case XKeys.BrowserRefresh: return Keys.WEB_REFRESH;
					case XKeys.BrowserStop: return Keys.WEB_STOP;
					case XKeys.BrowserForward: return Keys.WEB_FORWARD;
					case XKeys.BrowserBack: return Keys.WEB_BACK;
					//case XKeys.MY_COMPUTER: return Keys.MY_COMPUTER;
					//case XKeys.LaunchMail: return Keys.MAIL;
					case XKeys.SelectMedia: return Keys.MEDIA_SELECT;
				}
				throw new NotSupportedException($"{key} is not supported");
			}
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "KeyHit")]private static extern int KeyHit_internal(Keys key);
		public static int KeyHit(Keys key)
		{
			if(B3DGame.IsFocused()){return KeyHit_internal(key);}
			return Keyboard.KeyHit((int)key);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "KeyDown")]private static extern bool KeyDown_internal(Keys key);
		public static bool KeyDown(Keys key)
		{
			if(B3DGame.IsFocused()){return KeyDown_internal(key);}
			return Keyboard.KeyDown((int)key);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "GetKey")]private static extern int GetKey_internal();
		public static int GetKey()
		{
			if(B3DGame.IsFocused()){return GetKey_internal();}
			return Keyboard.GetKey();
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "WaitKey")]private static extern Keys WaitKey_internal();
		public static Keys WaitKey()
		{
			if(B3DGame.IsFocused()){return WaitKey_internal();}
			return (Keys)Keyboard.WaitKey();
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "FlushKeys")]private static extern void FlushKeys_internal();
		public static void FlushKeys()
		{
			if(B3DGame.IsFocused()){FlushKeys_internal();}

			Keyboard.Flush();
		}

		public sealed class B3DMouse:B3DDevice
		{
			public const int LeftButton = 1;
			public const int RightButton = 2;
			public const int MiddleButton = 3;
			public const int XButton1 = 4;
			public const int XButton2 = 5;

			public int X,Y,Z;
			public int dX,dY,dZ;

			public override void Update()
			{
				MouseState state = Microsoft.Xna.Framework.Input.Mouse.GetState();
				SetDownState(LeftButton, state.LeftButton!=0);
				SetDownState(RightButton, state.RightButton!=0);
				SetDownState(MiddleButton, state.MiddleButton!=0);
				SetDownState(XButton1, state.XButton1!=0);
				SetDownState(XButton2, state.XButton2!=0);
				//TODO: Bounds checking on coords.
				dX = X - state.X;
				dY = Y - state.Y;
				dZ = Z - state.ScrollWheelValue/120;
				X = state.X;
				Y = state.Y;
				Z = state.ScrollWheelValue/120;
			}

			public Point Position
			{
				get => new Point(X,Y);
				set
				{
					Microsoft.Xna.Framework.Input.Mouse.SetPosition(value.X,value.Y);
					(X,Y) = value;
				}
			}
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseDown")]private static extern bool MouseDown_internal(int button);
		public static bool MouseDown(int button)
		{
			if(B3DGame.IsFocused()){return MouseDown_internal(button);}
			return Mouse.KeyDown(button);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseHit")]private static extern int MouseHit_internal(int button);
		//TODO: This should return int.
		public static bool MouseHit(int button)
		{
			if(B3DGame.IsFocused()){return MouseHit_internal(button)>0;}
			return Mouse.KeyHit(button)>0;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "GetMouse")]private static extern int GetMouse_internal();
		public static int GetMouse()
		{
			if(B3DGame.IsFocused()){return GetMouse_internal();}
			return Mouse.GetKey();
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "WaitMouse")]private static extern int WaitMouse_internal();
		public static int WaitMouse()
		{
			if(B3DGame.IsFocused()){return WaitMouse_internal();}
			return Mouse.WaitKey();
		}
		public static int MouseWait() => WaitMouse();

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseX")]private static extern int MouseX_internal();
		public static int MouseX()
		{
			if(B3DGame.IsFocused()){return MouseX_internal();}
			return Mouse.X;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseY")]private static extern int MouseY_internal();
		public static int MouseY()
		{
			if(B3DGame.IsFocused()){return MouseY_internal();}
			return Mouse.Y;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseZ")]private static extern int MouseZ_internal();
		public static int MouseZ()
		{
			if(B3DGame.IsFocused()){return MouseZ_internal();}
			return Mouse.Z;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseXSpeed")]private static extern int MouseXSpeed_internal();
		public static int MouseXSpeed()
		{
			if(B3DGame.IsFocused()){return MouseXSpeed_internal();}
			return Mouse.dX;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseYSpeed")]private static extern int MouseYSpeed_internal();
		public static int MouseYSpeed()
		{
			if(B3DGame.IsFocused()){return MouseYSpeed_internal();}
			return Mouse.dY;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MouseZSpeed")]private static extern int MouseZSpeed_internal();
		public static int MouseZSpeed()
		{
			if(B3DGame.IsFocused()){return MouseZSpeed_internal();}
			return Mouse.dZ;
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "FlushMouse")]private static extern void FlushMouse_internal();
		public static void FlushMouse()
		{
			FlushMouse_internal();

			Mouse.Flush();
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "MoveMouse")]private static extern void MoveMouse_internal(int x, int y);
		public static void MoveMouse(int x, int y)
		{
			if(B3DGame.IsFocused())
			{
				Mouse.Position = new Point(x, y);
				MoveMouse_internal(x, y);
			}
			else
			{
				MoveMouse_internal(x, y);
				Mouse.Position = new Point(x, y);
			}

		}

		//public sealed class B3DJoystick:B3DDevice
		//{
		//	public readonly int Port;
		//	public readonly int Type;
		//	public int poll_time;
		//	public (int min, int max)[] ranges = new (int min, int max)[12];

		//	public B3DJoystick(int port, int type)
		//	{
		//		Port = port;
		//		Type = type;

		//		JoystickCapabilities capabilities = Joystick.GetCapabilities(port);
		//	}

		//	public override void Update()
		//	{
		//		JoystickState state = Joystick.GetState(Port);
		//	}
		//}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyType")]private static extern int JoyType_internal(int port = 0);
		public static int JoyType(int port = 0)
		{
			return JoyType_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyDown")]private static extern bool JoyDown_internal(int button, int port = 0);
		public static bool JoyDown(int button, int port = 0)
		{
			return JoyDown_internal(button, port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyHit")]private static extern bool JoyHit_internal(int button, int port = 0);
		public static bool JoyHit(int button, int port = 0)
		{
			return JoyHit_internal(button,port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "GetJoy")]private static extern int GetJoy_internal(int port = 0);
		public static int GetJoy(int port = 0)
		{
			return GetJoy_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "WaitJoy")]private static extern int WaitJoy_internal(int port = 0);
		public static int WaitJoy(int port = 0)
		{
			return WaitJoy_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyWait")]private static extern int JoyWait_internal(int port = 0);
		public static int JoyWait(int port = 0)
		{
			return JoyWait_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyX")]private static extern float JoyX_internal(int port = 0);
		public static float JoyX(int port = 0)
		{
			return JoyX_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyY")]private static extern float JoyY_internal(int port = 0);
		public static float JoyY(int port = 0)
		{
			return JoyY_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyZ")]private static extern float JoyZ_internal(int port = 0);
		public static float JoyZ(int port = 0)
		{
			return JoyZ_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyU")]private static extern float JoyU_internal(int port = 0);
		public static float JoyU(int port = 0)
		{
			return JoyU_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyV")]private static extern float JoyV_internal(int port = 0);
		public static float JoyV(int port = 0)
		{
			return JoyV_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyPitch")]private static extern float JoyPitch_internal(int port = 0);
		public static float JoyPitch(int port = 0)
		{
			return JoyPitch_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyYaw")]private static extern float JoyYaw_internal(int port = 0);
		public static float JoyYaw(int port = 0)
		{
			return JoyYaw_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyRoll")]private static extern float JoyRoll_internal(int port = 0);
		public static float JoyRoll(int port = 0)
		{
			return JoyRoll_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyHat")]private static extern int JoyHat_internal(int port = 0);
		public static int JoyHat(int port = 0)
		{
			return JoyHat_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyXDir")]private static extern int JoyXDir_internal(int port = 0);
		public static int JoyXDir(int port = 0)
		{
			return JoyXDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyYDir")]private static extern int JoyYDir_internal(int port = 0);
		public static int JoyYDir(int port = 0)
		{
			return JoyYDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyZDir")]private static extern int JoyZDir_internal(int port = 0);
		public static int JoyZDir(int port = 0)
		{
			return JoyZDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyUDir")]private static extern int JoyUDir_internal(int port = 0);
		public static int JoyUDir(int port = 0)
		{
			return JoyUDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyVDir")]private static extern int JoyVDir_internal(int port = 0);
		public static int JoyVDir(int port = 0)
		{
			return JoyVDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyPitchDir")]private static extern int JoyPitchDir_internal(int port = 0);
		public static int JoyPitchDir(int port = 0)
		{
			return JoyPitchDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyYawDir")]private static extern int JoyYawDir_internal(int port = 0);
		public static int JoyYawDir(int port = 0)
		{
			return JoyYawDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "JoyRollDir")]private static extern int JoyRollDir_internal(int port = 0);
		public static int JoyRollDir(int port = 0)
		{
			return JoyRollDir_internal(port);
		}

		[DllImport(Blitz3D.B3DDllLink, EntryPoint = "FlushJoy")]private static extern void FlushJoy_internal();
		public static void FlushJoy()
		{
			FlushJoy_internal();
		}



		[DllImport(Blitz3D.B3DDllLink)]private static extern void EnableDirectInput(bool enable);
		[DllImport(Blitz3D.B3DDllLink)]private static extern bool DirectInputEnabled();
		public static bool DirectInput
		{
			get => DirectInputEnabled();
			set => EnableDirectInput(value);
		}
		
	}
	public static partial class Blitz3D
	{
		// -----
		// Input
		// -----

		//TODO: Should return int
		public static bool KeyHit(Keys key) => B3DInput.KeyHit(key)>0;
		public static bool KeyDown(Keys key) => B3DInput.KeyDown(key);
		public static int GetKey() => B3DInput.GetKey();
		public static Keys WaitKey() => B3DInput.WaitKey();
		public static void FlushKeys() => B3DInput.FlushKeys();
		public static bool MouseDown(int button) => B3DInput.MouseDown(button);
		public static bool MouseHit(int button) => B3DInput.MouseHit(button);
		public static int GetMouse() => B3DInput.GetMouse();
		public static int WaitMouse() => B3DInput.WaitMouse();
		public static int MouseWait() => B3DInput.MouseWait();
		public static int MouseX() => B3DInput.MouseX();
		public static int MouseY() => B3DInput.MouseY();
		public static int MouseZ() => B3DInput.MouseZ();
		public static int MouseXSpeed() => B3DInput.MouseXSpeed();
		public static int MouseYSpeed() => B3DInput.MouseYSpeed();
		public static int MouseZSpeed() => B3DInput.MouseZSpeed();
		public static void FlushMouse() => B3DInput.FlushMouse();
		public static void MoveMouse(int x, int y) => B3DInput.MoveMouse(x, y);
		public static int JoyType(int port = 0) => B3DInput.JoyType(port);
		public static bool JoyDown(int button, int port = 0) => B3DInput.JoyDown(button, port);
		public static bool JoyHit(int button, int port = 0) => B3DInput.JoyHit(button,port);
		public static int GetJoy(int port = 0) => B3DInput.GetJoy(port);
		public static int WaitJoy(int port = 0) => B3DInput.WaitJoy(port);
		public static int JoyWait(int port = 0) => B3DInput.JoyWait(port);
		public static float JoyX(int port = 0) => B3DInput.JoyX(port);
		public static float JoyY(int port = 0) => B3DInput.JoyY(port);
		public static float JoyZ(int port = 0) => B3DInput.JoyZ(port);
		public static float JoyU(int port = 0) => B3DInput.JoyU(port);
		public static float JoyV(int port = 0) => B3DInput.JoyV(port);
		public static float JoyPitch(int port = 0) => B3DInput.JoyPitch(port);
		public static float JoyYaw(int port = 0) => B3DInput.JoyYaw(port);
		public static float JoyRoll(int port = 0) => B3DInput.JoyRoll(port);
		public static int JoyHat(int port = 0) => B3DInput.JoyHat(port);
		public static int JoyXDir(int port = 0) => B3DInput.JoyXDir(port);
		public static int JoyYDir(int port = 0) => B3DInput.JoyYDir(port);
		public static int JoyZDir(int port = 0) => B3DInput.JoyZDir(port);
		public static int JoyUDir(int port = 0) => B3DInput.JoyUDir(port);
		public static int JoyVDir(int port = 0) => B3DInput.JoyVDir(port);
		public static int JoyPitchDir(int port = 0) => B3DInput.JoyPitchDir(port);
		public static int JoyYawDir(int port = 0) => B3DInput.JoyYawDir(port);
		public static int JoyRollDir(int port = 0) => B3DInput.JoyRollDir(port);
		public static void FlushJoy() => B3DInput.FlushJoy();
		public static void EnableDirectInput(bool enable) => B3DInput.DirectInput = enable;
		public static bool DirectInputEnabled() => B3DInput.DirectInput;
	}
}
