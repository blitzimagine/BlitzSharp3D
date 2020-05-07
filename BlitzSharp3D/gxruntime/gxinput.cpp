
#include "std.h"
#include "gxinput.h"
#include "gxruntime.h"

#include "../bbruntime/bbsys.h"

#include <dinput.h>
#include <SDL_syswm.h>

static const int QUE_SIZE = 32;

class Device : public gxDevice {
public:
	bool acquired;
	gxInput* input;
	IDirectInputDevice7* device;

	Device(gxInput* i, IDirectInputDevice7* d) :input(i), acquired(false), device(d) {
	}
	virtual ~Device() {
		device->Release();
	}
	bool acquire() {
		return acquired = device->Acquire() >= 0;
	}
	void unacquire() {
		device->Unacquire();
		acquired = false;
	}
};

class Keyboard : public Device {
public:
	Keyboard(gxInput* i, IDirectInputDevice7* d) :Device(i, d) {
	}
	void update() {
		if (!acquired) {
			if (!input->runtime->idle())
				RTEX(0);
			return;
		}
		int k, cnt = 32;
		DIDEVICEOBJECTDATA data[32], * curr;
		if (device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), data, (DWORD*)&cnt, 0) < 0) return;
		curr = data;
		for (k = 0; k < cnt; ++curr, ++k) {
			int n = curr->dwOfs; if (!n || n > 255) continue;
			if (curr->dwData & 0x80) downEvent(n);
			else upEvent(n);
		}
	}
};

class Mouse : public Device {
public:
	Mouse(gxInput* i, IDirectInputDevice7* d) :Device(i, d) {
	}
	void update() {
		if (!acquired) {
			if (!input->runtime->idle())
				RTEX(0);
			return;
		}
		DIMOUSESTATE state;
		if (device->GetDeviceState(sizeof(state), &state) < 0) return;
		if (gxGraphics* g = input->runtime->graphics) {
			int mx = (int)(axis_states[0] + state.lX);
			int my = (int)(axis_states[1] + state.lY);
			if (mx < 0) mx = 0;
			else if (mx >= g->getWidth()) mx = g->getWidth() - 1;
			if (my < 0) my = 0;
			else if (my >= g->getHeight()) my = g->getHeight() - 1;
			axis_states[0] = (float)mx;
			axis_states[1] = (float)my;
			axis_states[2] += (float)state.lZ;
		}
		for (int k = 0; k < 3; ++k) {
			setDownState(k + 1, state.rgbButtons[k] & 0x80 ? true : false);
		}
	}
};

class Joystick : public Device {
public:
	int type, poll_time;
	int mins[12], maxs[12];
	Joystick(gxInput* i, IDirectInputDevice7* d, int t) :Device(i, d), type(t), poll_time(0) {
		for (int k = 0; k < 12; ++k) {
			//initialize joystick axis ranges (d'oh!)
			DIPROPRANGE range;
			range.diph.dwSize = sizeof(DIPROPRANGE);
			range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			range.diph.dwObj = k * 4 + 12;
			range.diph.dwHow = DIPH_BYOFFSET;
			if (d->GetProperty(DIPROP_RANGE, &range.diph) < 0) {
				mins[k] = 0;
				maxs[k] = 65535;
				continue;
			}
			mins[k] = range.lMin;
			maxs[k] = range.lMax - range.lMin;
		}
	}
	void update() {
		unsigned tm = timeGetTime();
		if (tm - poll_time < 3) return;
		if (device->Poll() < 0) {
			acquired = false;
			if (!input->runtime->idle())
				RTEX(0);
			acquire(); if (device->Poll() < 0) return;
		}
		poll_time = tm;
		DIJOYSTATE state;
		if (device->GetDeviceState(sizeof(state), &state) < 0) return;
		axis_states[0] = (state.lX - mins[0]) / (float)maxs[0] * 2 - 1;
		axis_states[1] = (state.lY - mins[1]) / (float)maxs[1] * 2 - 1;
		axis_states[2] = (state.lZ - mins[2]) / (float)maxs[2] * 2 - 1;
		axis_states[3] = (state.rglSlider[0] - mins[6]) / (float)maxs[6] * 2 - 1;
		axis_states[4] = (state.rglSlider[1] - mins[7]) / (float)maxs[7] * 2 - 1;
		axis_states[5] = (state.lRx - mins[3]) / (float)maxs[3] * 2 - 1;
		axis_states[6] = (state.lRy - mins[4]) / (float)maxs[4] * 2 - 1;
		axis_states[7] = (state.lRz - mins[5]) / (float)maxs[5] * 2 - 1;
		if ((state.rgdwPOV[0] & 0xffff) == 0xffff) axis_states[8] = -1;
		else axis_states[8] = floor(state.rgdwPOV[0] / 100.0f + .5f);

		for (int k = 0; k < 31; ++k) {
			setDownState(k + 1, state.rgbButtons[k] & 0x80 ? true : false);
		}
	}
};

static Keyboard* keyboard;
static Mouse* mouse;
static vector<Joystick*> joysticks;

static Keyboard* createKeyboard(gxInput* input) {
	IDirectInputDevice7* dev;
	if (input->dirInput->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7, (void**)&dev, 0) >= 0) {
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		SDL_GetWindowWMInfo(input->runtime->window, &info); // TEMPORARY
		if (dev->SetCooperativeLevel(info.info.win.window, DISCL_FOREGROUND | DISCL_EXCLUSIVE) >= 0) {

			if (dev->SetDataFormat(&c_dfDIKeyboard) >= 0) {
				DIPROPDWORD dword;
				memset(&dword, 0, sizeof(dword));
				dword.diph.dwSize = sizeof(DIPROPDWORD);
				dword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
				dword.diph.dwObj = 0;
				dword.diph.dwHow = DIPH_DEVICE;
				dword.dwData = 32;
				if (dev->SetProperty(DIPROP_BUFFERSIZE, &dword.diph) >= 0) {
					return d_new Keyboard(input, dev);
				}
				else {
					//					input->runtime->debugInfo( "keyboard: SetProperty failed" );
				}
			}
			else {
				//				input->runtime->debugInfo( "keyboard: SetDataFormat failed" );
			}
			return d_new Keyboard(input, dev);

		}
		else {
			input->runtime->debugInfo("keyboard: SetCooperativeLevel failed");
		}
		dev->Release();
	}
	else {
		input->runtime->debugInfo("keyboard: CreateDeviceEx failed");
	}
	return 0;
}

static Mouse* createMouse(gxInput* input) {
	IDirectInputDevice7* dev;
	if (input->dirInput->CreateDeviceEx(GUID_SysMouse, IID_IDirectInputDevice7, (void**)&dev, 0) >= 0) {
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		SDL_GetWindowWMInfo(input->runtime->window, &info); // TEMPORARY
		if (dev->SetCooperativeLevel(info.info.win.window, DISCL_FOREGROUND | DISCL_EXCLUSIVE) >= 0) {

			if (dev->SetDataFormat(&c_dfDIMouse) >= 0) {
				return d_new Mouse(input, dev);
			}
			else {
				//				input->runtime->debugInfo( "mouse: SetDataFormat failed" );
			}
			return d_new Mouse(input, dev);

		}
		else {
			input->runtime->debugInfo("mouse: SetCooperativeLevel failed");
		}
		dev->Release();
	}
	else {
		input->runtime->debugInfo("mouse: CreateDeviceEx failed");
	}
	return 0;
}

static Joystick* createJoystick(gxInput* input, LPCDIDEVICEINSTANCE devinst) {
	IDirectInputDevice7* dev;
	if (input->dirInput->CreateDeviceEx(devinst->guidInstance, IID_IDirectInputDevice7, (void**)&dev, 0) >= 0) {
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		SDL_GetWindowWMInfo(input->runtime->window, &info); // TEMPORARY
		if (dev->SetCooperativeLevel(info.info.win.window, DISCL_FOREGROUND | DISCL_EXCLUSIVE) >= 0) {
			if (dev->SetDataFormat(&c_dfDIJoystick) >= 0) {
				int t = ((devinst->dwDevType >> 8) & 0xff) == DIDEVTYPEJOYSTICK_GAMEPAD ? 1 : 2;
				return d_new Joystick(input, dev, t);
			}
		}
		dev->Release();
	}
	return 0;
}

static BOOL CALLBACK enumJoystick(LPCDIDEVICEINSTANCE devinst, LPVOID pvRef) {

	if ((devinst->dwDevType & 0xff) != DIDEVTYPE_JOYSTICK) return DIENUM_CONTINUE;

	if (Joystick* joy = createJoystick((gxInput*)pvRef, devinst)) {
		joysticks.push_back(joy);
	}
	return DIENUM_CONTINUE;
}

gxInput::gxInput(gxRuntime* rt, IDirectInput7* di) :
	runtime(rt), dirInput(di) {
	keyboard = createKeyboard(this);
	mouse = createMouse(this);
	joysticks.clear();
	dirInput->EnumDevices(DIDEVTYPE_JOYSTICK, enumJoystick, this, DIEDFL_ATTACHEDONLY);
}

gxInput::~gxInput() {
	for (int k = 0; k < (int)joysticks.size(); ++k) delete joysticks[k];
	joysticks.clear();
	delete mouse;
	delete keyboard;

	dirInput->Release();
}

static uint8_t SDLToBlitzScancode(gxInput* input, int key)
{
	switch (key)
	{
	case SDL_SCANCODE_ESCAPE: return 1;
	case SDL_SCANCODE_1: return 2;
	case SDL_SCANCODE_2: return 3;
	case SDL_SCANCODE_3: return 4;
	case SDL_SCANCODE_4: return 5;
	case SDL_SCANCODE_5: return 6;
	case SDL_SCANCODE_6: return 7;
	case SDL_SCANCODE_7: return 8;
	case SDL_SCANCODE_8: return 9;
	case SDL_SCANCODE_9: return 10;
	case SDL_SCANCODE_0: return 11;
	case SDL_SCANCODE_MINUS: return 12;
	case SDL_SCANCODE_EQUALS: return 13;
	case SDL_SCANCODE_BACKSPACE: return 14;
	case SDL_SCANCODE_TAB: return 15;
	case SDL_SCANCODE_Q: return 16;
	case SDL_SCANCODE_W: return 17;
	case SDL_SCANCODE_E: return 18;
	case SDL_SCANCODE_R: return 19;
	case SDL_SCANCODE_T: return 20;
	case SDL_SCANCODE_Y: return 21;
	case SDL_SCANCODE_U: return 22;
	case SDL_SCANCODE_I: return 23;
	case SDL_SCANCODE_O: return 24;
	case SDL_SCANCODE_P: return 25;
	case SDL_SCANCODE_LEFTBRACKET: return 26;
	case SDL_SCANCODE_RIGHTBRACKET: return 27;
	case SDL_SCANCODE_RETURN: return 28;
	case SDL_SCANCODE_LCTRL: return 29;
	case SDL_SCANCODE_A: return 30;
	case SDL_SCANCODE_S: return 31;
	case SDL_SCANCODE_D: return 32;
	case SDL_SCANCODE_F: return 33;
	case SDL_SCANCODE_G: return 34;
	case SDL_SCANCODE_H: return 35;
	case SDL_SCANCODE_J: return 36;
	case SDL_SCANCODE_K: return 37;
	case SDL_SCANCODE_L: return 38;
	case SDL_SCANCODE_SEMICOLON: return 39;
	case SDL_SCANCODE_APOSTROPHE: return 40;
	case SDL_SCANCODE_GRAVE: return 41;
	case SDL_SCANCODE_LSHIFT: return 42;
	case SDL_SCANCODE_BACKSLASH: return 43;
	case SDL_SCANCODE_Z: return 44;
	case SDL_SCANCODE_X: return 45;
	case SDL_SCANCODE_C: return 46;
	case SDL_SCANCODE_V: return 47;
	case SDL_SCANCODE_B: return 48;
	case SDL_SCANCODE_N: return 49;
	case SDL_SCANCODE_M: return 50;
	case SDL_SCANCODE_COMMA: return 51;
	case SDL_SCANCODE_PERIOD: return 52;
	case SDL_SCANCODE_SLASH: return 53;
	case SDL_SCANCODE_RSHIFT: return 54;
	case SDL_SCANCODE_KP_MULTIPLY: return 55;
	case SDL_SCANCODE_LALT: return 56;
	case SDL_SCANCODE_SPACE: return 57;
	case SDL_SCANCODE_CAPSLOCK: return 58;
	case SDL_SCANCODE_F1: return 59;
	case SDL_SCANCODE_F2: return 60;
	case SDL_SCANCODE_F3: return 61;
	case SDL_SCANCODE_F4: return 62;
	case SDL_SCANCODE_F5: return 63;
	case SDL_SCANCODE_F6: return 64;
	case SDL_SCANCODE_F7: return 65;
	case SDL_SCANCODE_F8: return 66;
	case SDL_SCANCODE_F9: return 67;
	case SDL_SCANCODE_F10: return 68;
	case SDL_SCANCODE_NUMLOCKCLEAR: return 69;
	case SDL_SCANCODE_SCROLLLOCK: return 60;
	case SDL_SCANCODE_KP_7: return 71;
	case SDL_SCANCODE_KP_8: return 72;
	case SDL_SCANCODE_KP_9: return 73;
	case SDL_SCANCODE_KP_MINUS: return 74;
	case SDL_SCANCODE_KP_4: return 75;
	case SDL_SCANCODE_KP_5: return 76;
	case SDL_SCANCODE_KP_6: return 77;
	case SDL_SCANCODE_KP_PLUS: return 78;
	case SDL_SCANCODE_KP_1: return 79;
	case SDL_SCANCODE_KP_2: return 80;
	case SDL_SCANCODE_KP_3: return 81;
	case SDL_SCANCODE_KP_0: return 82;
	case SDL_SCANCODE_KP_PERIOD: return 83;
	case SDL_SCANCODE_NONUSBACKSLASH: return 86;
	case SDL_SCANCODE_F11: return 87;
	case SDL_SCANCODE_F12: return 88;
	case SDL_SCANCODE_F13: return 100;
	case SDL_SCANCODE_F14: return 101;
	case SDL_SCANCODE_F15: return 102;
	case SDL_SCANCODE_LANG3: return 112; // Kana
	case SDL_SCANCODE_INTERNATIONAL1: return 115; // /? on Portugese (Brazilian) keyboards
	case SDL_SCANCODE_INTERNATIONAL4: return 121; // CONVERT
	case SDL_SCANCODE_INTERNATIONAL5: return 123; // NOCONVERT
	case SDL_SCANCODE_INTERNATIONAL3: return 125; // Yen
	//case SDL_SCANCODE_KP_COMMA: return 126; // Numpad . on Portugese (Brazilian) keyboards

	case SDL_SCANCODE_KP_EQUALS: return 141;
	case SDL_SCANCODE_AUDIOPREV: return 144;
	case SDL_SCANCODE_KP_AT: return 145;
	case SDL_SCANCODE_KP_COLON: return 146;
		//UNDERLINE = 147,
		//KANJI = 148,
	case SDL_SCANCODE_STOP: return 149;
		//AX = 150, // Japan AX
		//Unlabeled = 151, // (J3100)
	case SDL_SCANCODE_AUDIONEXT: return 153;
	case SDL_SCANCODE_KP_ENTER: return 156;
	case SDL_SCANCODE_RCTRL: return 157;
	case SDL_SCANCODE_MUTE: return 160;
	case SDL_SCANCODE_CALCULATOR: return 161;
	case SDL_SCANCODE_AUDIOPLAY: return 162;
	case SDL_SCANCODE_AUDIOSTOP: return 164;
	case SDL_SCANCODE_VOLUMEDOWN: return 174;
	case SDL_SCANCODE_VOLUMEUP: return 176;
	case SDL_SCANCODE_AC_HOME: return 178;
	case SDL_SCANCODE_KP_COMMA: return 179;
	case SDL_SCANCODE_KP_DIVIDE: return 181;
	case SDL_SCANCODE_SYSREQ: return 183;
	case SDL_SCANCODE_RALT: return 184;
	case SDL_SCANCODE_PAUSE: return 197;
	case SDL_SCANCODE_HOME: return 199;
	case SDL_SCANCODE_UP: return 200;
	case SDL_SCANCODE_PAGEUP: return 201;
	case SDL_SCANCODE_LEFT: return 203;
	case SDL_SCANCODE_RIGHT: return 205;
	case SDL_SCANCODE_END: return 207;
	case SDL_SCANCODE_DOWN: return 208;
	case SDL_SCANCODE_PAGEDOWN: return 209;
	case SDL_SCANCODE_INSERT: return 210;
	case SDL_SCANCODE_DELETE: return 211;
	case SDL_SCANCODE_LGUI: return 219;
	case SDL_SCANCODE_RGUI: return 220;
	case SDL_SCANCODE_APPLICATION: return 221;
	case SDL_SCANCODE_POWER: return 222;
	case SDL_SCANCODE_SLEEP: return 223;
		//WAKE = 227,
	case SDL_SCANCODE_AC_SEARCH: return 229;
	case SDL_SCANCODE_AC_BOOKMARKS: return 230;
	case SDL_SCANCODE_AC_REFRESH: return 231;
	case SDL_SCANCODE_AC_STOP: return 232;
	case SDL_SCANCODE_AC_FORWARD: return 233;
	case SDL_SCANCODE_AC_BACK: return 234;
	case SDL_SCANCODE_COMPUTER: return 235;
	case SDL_SCANCODE_MAIL: return 236;
	case SDL_SCANCODE_MEDIASELECT: return 237;

	default:
		return -1;
	}
}

void gxInput::wm_keydown(int key) {
	if (keyboard) keyboard->downEvent(SDLToBlitzScancode(this, key));
}

void gxInput::wm_keyup(int key) {
	if (keyboard) keyboard->upEvent(SDLToBlitzScancode(this, key));
}

void gxInput::wm_mousedown(int key) {
	if (mouse) mouse->downEvent(key);
}

void gxInput::wm_mouseup(int key) {
	if (mouse) mouse->upEvent(key);
}

void gxInput::wm_mousemove(int x, int y) {
	if (mouse) {
		mouse->axis_states[0] = (float)x;
		mouse->axis_states[1] = (float)y;
	}
}

void gxInput::wm_mousewheel(int dz) {
	if (mouse) mouse->axis_states[2] += dz;
}

void gxInput::reset() {
	if (mouse) mouse->reset();
	if (keyboard) keyboard->reset();
	for (int k = 0; k < (int)joysticks.size(); ++k) joysticks[k]->reset();
}

bool gxInput::acquire() {
	bool m_ok = true, k_ok = true;
	if (mouse) m_ok = mouse->acquire();
	if (keyboard) k_ok = keyboard->acquire();
	if (m_ok && k_ok) return true;
	if (k_ok) keyboard->unacquire();
	if (m_ok) mouse->unacquire();
	return false;
}

void gxInput::unacquire() {
	if (keyboard) keyboard->unacquire();
	if (mouse) mouse->unacquire();
}

void gxInput::moveMouse(int x, int y) {
	if (!mouse) return;
	mouse->axis_states[0] = (float)x;
	mouse->axis_states[1] = (float)y;
	runtime->moveMouse(x, y);
}

gxDevice* gxInput::getMouse()const {
	return mouse;
}

gxDevice* gxInput::getKeyboard()const {
	return keyboard;
}

gxDevice* gxInput::getJoystick(int n)const {
	return n >= 0 && n < (int)joysticks.size() ? joysticks[n] : 0;
}

int gxInput::getJoystickType(int n)const {
	return n >= 0 && n < (int)joysticks.size() ? joysticks[n]->type : 0;
}

int gxInput::numJoysticks()const {
	return joysticks.size();
}

int gxInput::toAscii(int scan)const {
	switch (scan) {
	case DIK_INSERT:return ASC_INSERT;
	case DIK_DELETE:return ASC_DELETE;
	case DIK_HOME:return ASC_HOME;
	case DIK_END:return ASC_END;
	case DIK_PGUP:return ASC_PAGEUP;
	case DIK_PGDN:return ASC_PAGEDOWN;
	case DIK_UP:return ASC_UP;
	case DIK_DOWN:return ASC_DOWN;
	case DIK_LEFT:return ASC_LEFT;
	case DIK_RIGHT:return ASC_RIGHT;
	}
	scan &= 0x7f;
	int virt = MapVirtualKey(scan, 1);
	if (!virt) return 0;

	static unsigned char mat[256];
	mat[VK_LSHIFT] = keyboard->keyDown(DIK_LSHIFT) ? 0x80 : 0;
	mat[VK_RSHIFT] = keyboard->keyDown(DIK_RSHIFT) ? 0x80 : 0;
	mat[VK_SHIFT] = mat[VK_LSHIFT] | mat[VK_RSHIFT];
	mat[VK_LCONTROL] = keyboard->keyDown(DIK_LCONTROL) ? 0x80 : 0;
	mat[VK_RCONTROL] = keyboard->keyDown(DIK_RCONTROL) ? 0x80 : 0;
	mat[VK_CONTROL] = mat[VK_LCONTROL] | mat[VK_RCONTROL];
	mat[VK_LMENU] = keyboard->keyDown(DIK_LMENU) ? 0x80 : 0;
	mat[VK_RMENU] = keyboard->keyDown(DIK_RMENU) ? 0x80 : 0;
	mat[VK_MENU] = mat[VK_LMENU] | mat[VK_RMENU];

	WORD ch;
	if (ToAscii(virt, scan, mat, &ch, 0) != 1) return 0;
	return ch & 255;
}
