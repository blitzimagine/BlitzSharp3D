
#include "std.h"
#include "gxruntime.h"
#include "zmouse.h"

#include <SDL_syswm.h>

#include <VersionHelpers.h>
#include "..\stdutil\osversion.h"

#include "../bbruntime/bbsys.h"

//#define SPI_SETMOUSESPEED	113

struct gxRuntime::GfxMode {
	DDSURFACEDESC2 desc;
};
struct gxRuntime::GfxDriver {
	GUID* guid;
	std::string name;
	std::vector<GfxMode*> modes;
#ifdef PRO
	D3DDEVICEDESC7 d3d_desc;
#endif
};

static const int static_ws = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
static const int scaled_ws = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

static string app_title;
static string app_close;
static gxRuntime* runtime;
static bool busy, suspended;
static volatile bool run_flag;
static DDSURFACEDESC2 desktop_desc;

typedef int(_stdcall* LibFunc)(const void* in, int in_sz, void* out, int out_sz);

struct gxDll {
	HINSTANCE hinst;
	map<string, LibFunc> funcs;
};

static map<string, gxDll*> libs;

//static LRESULT CALLBACK windowProc( HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam );
static int __cdecl eventProc(void* userdata, SDL_Event* event);

//current gfx mode
//
//0=NONE
//1=SCALED WINDOW
//2=FIXED SIZE WINDOW
//3=EXCLUSIVE
//
static int gfx_mode;
static bool gfx_lost;
static bool is_focused;
static bool auto_suspend;

//for modes 1 and 2
static int mod_cnt;
static MMRESULT timerID;
static IDirectDrawClipper* clipper;
static IDirectDrawSurface7* primSurf;

static set<gxTimer*> timers;

enum {
	WM_STOP = WM_USER + 1, WM_RUN, WM_END
};

////////////////////
// STATIC STARTUP //
////////////////////
gxRuntime* gxRuntime::openRuntime(HINSTANCE hinst, const string& cmd_line) {
	if (runtime) return 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		runtimeError("Failed to initialise SDL.");
		return nullptr;
	}

	SDL_Window* window = SDL_CreateWindow("Blitz Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, 0);
	if (window == nullptr)
	{
		runtimeError("Failed to create window.");
		return nullptr;
	}
	is_focused = true;

	SDL_SetEventFilter(::eventProc, nullptr);

	//create WNDCLASS
	/*WNDCLASS wndclass;
	memset(&wndclass,0,sizeof(wndclass));
	wndclass.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	wndclass.lpfnWndProc=::windowProc;
	wndclass.hInstance=hinst;
	wndclass.lpszClassName="Blitz Runtime Class";
	wndclass.hCursor=(HCURSOR)LoadCursor( 0,IDC_ARROW );
	wndclass.hbrBackground=(HBRUSH)GetStockObject( BLACK_BRUSH );
	RegisterClass( &wndclass );*/

	gfx_mode = 0;
	clipper = 0; primSurf = 0;
	busy = suspended = false;
	run_flag = true;

	/*const char *app_t=" ";
	int ws=WS_CAPTION,ws_ex=0;

	HWND hwnd=CreateWindowEx( ws_ex,"Blitz Runtime Class",app_t,ws,0,0,0,0,0,0,0,0 );

	UpdateWindow( hwnd );*/

	runtime = d_new gxRuntime(hinst, cmd_line, window);
	return runtime;
}

void gxRuntime::closeRuntime(gxRuntime* r) {
	if (!runtime || runtime != r) return;

	map<string, gxDll*>::const_iterator it;
	for (it = libs.begin(); it != libs.end(); ++it) {
		FreeLibrary(it->second->hinst);
	}
	libs.clear();

	delete runtime;
	runtime = 0;

}

//////////////////////////
// RUNTIME CONSTRUCTION //
//////////////////////////
typedef int(_stdcall* SetAppCompatDataFunc)(int x, int y);

gxRuntime::gxRuntime(HINSTANCE hi, const string& cl, SDL_Window* window) :
	hinst(hi), cmd_line(cl), window(window), curr_driver(0), enum_all(false),
	pointer_visible(true), audio(0), input(0), graphics(0), fileSystem(0), use_di(false) {

	CoInitialize(0);

	enumGfx();
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(tc));
	timeBeginPeriod(tc.wPeriodMin);

	//memset(&osinfo, 0, sizeof(osinfo));
	//osinfo.dwOSVersionInfoSize = sizeof(osinfo);
	//GetVersionEx(&osinfo);

	HMODULE ddraw = LoadLibraryA("ddraw.dll");
	if (ddraw) {
		SetAppCompatDataFunc SetAppCompatData = (SetAppCompatDataFunc)GetProcAddress(ddraw, "SetAppCompatData");
		if (SetAppCompatData) SetAppCompatData(12, 0);
		FreeLibrary(ddraw);
	}
}

gxRuntime::~gxRuntime() {
	while (timers.size()) freeTimer(*timers.begin());
	if (audio) closeAudio(audio);
	if (graphics) closeGraphics(graphics);
	if (input) closeInput(input);
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(tc));
	timeEndPeriod(tc.wPeriodMin);
	denumGfx();
	SDL_DestroyWindow(window);
	//UnregisterClass( "Blitz Runtime Class",hinst );
	SDL_Quit();

	CoUninitialize();
}

void gxRuntime::pauseAudio() {
	if (audio) audio->pause();
}

void gxRuntime::resumeAudio() {
	if (audio) audio->resume();
}

void gxRuntime::backupGraphics() {
	if (auto_suspend) {
		graphics->backup();
	}
}

void gxRuntime::restoreGraphics() {
	if (auto_suspend) {
		if (!graphics->restore()) gfx_lost = true;
	}
}

void gxRuntime::resetInput() {
	if (input) input->reset();
}

void gxRuntime::acquireInput() {
	if (!input) return;
	if (gfx_mode == 3) {
		if (use_di) {
			use_di = input->acquire();
		}
		else {
		}
	}
	input->reset();
}

void gxRuntime::unacquireInput() {
	if (!input) return;
	if (gfx_mode == 3 && use_di) input->unacquire();
	input->reset();
}

/////////////
// SUSPEND //
/////////////
void gxRuntime::suspend() {
	busy = true;
	pauseAudio();
	backupGraphics();
	unacquireInput();
	suspended = true;
	busy = false;

	if (gfx_mode == 3) ShowCursor(1);
}

////////////
// RESUME //
////////////
void gxRuntime::resume() {
	if (gfx_mode == 3) ShowCursor(0);
	busy = true;
	acquireInput();
	restoreGraphics();
	resumeAudio();
	suspended = false;
	busy = false;
}

///////////////////
// FORCE SUSPEND //
///////////////////
void gxRuntime::forceSuspend() {
	if (gfx_mode == 3) {
		// TODO
		SetForegroundWindow(GetDesktopWindow());
		ShowWindow(GetDesktopWindow(), SW_SHOW);
	}
	else {
		suspend();
	}
}

//////////////////
// FORCE RESUME //
//////////////////
void gxRuntime::forceResume() {
	if (gfx_mode == 3) {
		SDL_RaiseWindow(window);
		SDL_MaximizeWindow(window);
	}
	else {
		resume();
	}
}

///////////
// PAINT //
///////////
void gxRuntime::paint() {
	switch (gfx_mode) {
	case 0:
	{
	}
	break;
	case 1:case 2:	//scaled windowed mode.
	{
		int srcTop, srcLeft, srcBottom, srcRight;
		int destTop, destLeft, destBottom, destRight;
		srcLeft = srcTop = 0;
		SDL_GetWindowPosition(window, &destLeft, &destTop);
		SDL_GetWindowSize(window, &destRight, &destBottom);
		srcRight = (gfx_mode == 1) ? graphics->getWidth() : destRight;
		srcBottom = (gfx_mode == 1) ? graphics->getHeight() : destBottom;
		destRight += destLeft;
		destBottom += destTop;
		gxCanvas* f = graphics->getFrontCanvas();
		RECT src = { srcLeft, srcTop, srcRight, srcBottom };
		RECT dest = { destLeft, destTop, destRight, destBottom };
		primSurf->Blt(&dest, f->getSurface(), &src, 0, 0);
	}
	break;
	case 3:
	{
		//exclusive mode
	}
	break;
	}
}

//////////
// FLIP //
//////////
void gxRuntime::flip(bool vwait) {
	gxCanvas* b = graphics->getBackCanvas();
	gxCanvas* f = graphics->getFrontCanvas();
	int n;
	switch (gfx_mode) {
	case 1:case 2:
		if (vwait) graphics->vwait();
		f->setModify(b->getModify());
		if (f->getModify() != mod_cnt) {
			mod_cnt = f->getModify();
			paint();
		}
		break;
	case 3:
		if (vwait) {
			BOOL vb;
			while (graphics->dirDraw->GetVerticalBlankStatus(&vb) >= 0 && vb) {}
			n = f->getSurface()->Flip(0, DDFLIP_WAIT);
		}
		else {
			n = f->getSurface()->Flip(0, DDFLIP_NOVSYNC | DDFLIP_WAIT);
		}
		if (n >= 0) return;
		string t = "Flip Failed! Return code:" + itoa(n & 0x7fff);
		debugLog(t.c_str());
		break;
	}
}

////////////////
// MOVE MOUSE //
////////////////
void gxRuntime::moveMouse(int x, int y) {
	switch (gfx_mode) {
	case 1:
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		x = x * w / graphics->getWidth();
		y = y * h / graphics->getHeight();
	case 2:
		int winX, winY;
		SDL_GetWindowPosition(window, &winX, &winY);
		x += winX; y += winY;
		break;
	case 3:
		if (use_di) return;
		break;
	default:
		return;
	}
	SetCursorPos(x, y);
}

/////////////////
// WINDOW PROC //
/////////////////
int gxRuntime::eventProc(void* userdata, SDL_Event* event)
{
	if (busy)
		return 1;

	Uint32 windowID = SDL_GetWindowID(window);

	if (event->type == SDL_WINDOWEVENT && event->window.windowID == windowID)
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_EXPOSED:
			if (gfx_mode && !auto_suspend) {
				if (!graphics->restore()) gfx_lost = true;
			}
			SDL_SysWMinfo info;
			SDL_VERSION(&info.version);
			SDL_GetWindowWMInfo(window, &info); // TEMPORARY
			PAINTSTRUCT ps;
			BeginPaint(info.info.win.window, &ps);
			paint();
			EndPaint(info.info.win.window, &ps);
			return 1;

		case SDL_WINDOWEVENT_CLOSE:
			if (app_close.size()) {
				const SDL_MessageBoxButtonData buttons[] = {
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel" },
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK" },
				};
				const SDL_MessageBoxData messageboxdata = {
					SDL_MESSAGEBOX_WARNING,
					window,
					app_title.c_str(),
					app_close.c_str(),
					SDL_arraysize(buttons),
					buttons,
					NULL
				};
				int buttonID;
				SDL_ShowMessageBox(&messageboxdata, &buttonID);
				if (buttonID != 1) return 0;
			}
			asyncEnd();
			return 0;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			is_focused = true;
			if (auto_suspend && suspended) resume();
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			is_focused = false;
			if (auto_suspend && !suspended) suspend();
			break;
		}
	}

	if (!input || suspended) return 1;

	if (gfx_mode == 3 && use_di) {
		use_di = input->acquire();
		return 1;
	}

	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.windowID != windowID) return 1;

		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			input->wm_mousedown(1);
			break;
		case SDL_BUTTON_RIGHT:
			input->wm_mousedown(2);
			break;
		case SDL_BUTTON_MIDDLE:
			input->wm_mousedown(3);
			break;
		}

		//SDL_RaiseWindow(window);
		SDL_CaptureMouse(SDL_TRUE);
		break;

	case SDL_MOUSEBUTTONUP:
		if (event->button.windowID != windowID) return 1;

		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			input->wm_mouseup(1);
			break;
		case SDL_BUTTON_RIGHT:
			input->wm_mouseup(2);
			break;
		case SDL_BUTTON_MIDDLE:
			input->wm_mouseup(3);
			break;
		default:
			SDL_CaptureMouse(SDL_FALSE);
			break;
		}

		break;

	case SDL_MOUSEMOTION:
		if (event->motion.windowID != windowID) return 1;

		if (!graphics) break;
		if (gfx_mode == 3 && !use_di) {
			POINT p; GetCursorPos(&p); // TODO
			input->wm_mousemove(p.x, p.y);
		}
		else {
			int x = event->motion.x, y = event->motion.y;
			if (gfx_mode == 1) {
				int w, h;
				SDL_GetWindowSize(window, &w, &h);
				x = x * graphics->getWidth() / w;
				y = y * graphics->getHeight() / h;
			}
			if (x < 0) x = 0;
			else if (x >= graphics->getWidth()) x = graphics->getWidth() - 1;
			if (y < 0) y = 0;
			else if (y >= graphics->getHeight()) y = graphics->getHeight() - 1;
			input->wm_mousemove(x, y);
		}
		break;

	case SDL_MOUSEWHEEL:
		if (event->wheel.windowID != windowID) return 1;
		input->wm_mousewheel(event->wheel.y * WHEEL_DELTA);
		break;

	case SDL_KEYDOWN:
		if (event->key.windowID != windowID || event->key.repeat) return 1;
		input->wm_keydown(event->key.keysym.scancode);
		break;

	case SDL_KEYUP:
		if (event->key.windowID != windowID || event->key.repeat) return 1;
		input->wm_keyup(event->key.keysym.scancode);
		break;
	}

	return 1;
}

static int __cdecl eventProc(void* userdata, SDL_Event* event)
{
	if (runtime) return runtime->eventProc(userdata, event);
	return 1;
}

/*LRESULT gxRuntime::windowProc( HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam ){

	if( busy ){
		return DefWindowProc( hwnd,msg,wparam,lparam );
	}

	PAINTSTRUCT ps;

	//handle 'special' messages!
	switch( msg ){
	case WM_PAINT:
		if( gfx_mode && !auto_suspend ){
			if( !graphics->restore() ) gfx_lost=true;
		}
		BeginPaint( hwnd,&ps );
		paint();
		EndPaint( hwnd,&ps );
		return DefWindowProc( hwnd,msg,wparam,lparam );
	case WM_ERASEBKGND:
		return gfx_mode ? 1 : DefWindowProc( hwnd,msg,wparam,lparam );
	case WM_CLOSE:
		if( app_close.size() ){
			int n=MessageBox( hwnd,app_close.c_str(),app_title.c_str(),MB_OKCANCEL|MB_ICONWARNING|MB_SETFOREGROUND|MB_TOPMOST );
			if( n!=IDOK ) return 0;
		}
		asyncEnd();
		return 0;
	case WM_SETCURSOR:
		if( !suspended ){
			if( gfx_mode==3 ){
				SetCursor( 0 );
				return 1;
			}else if( !pointer_visible ){
				POINT p;
				GetCursorPos( &p );
				ScreenToClient( hwnd,&p );
				RECT r;GetClientRect( hwnd,&r );
				if( p.x>=0 && p.y>=0 && p.x<r.right && p.y<r.bottom ){
					SetCursor( 0 );
					return 1;
				}
			}
		}
		break;
	case WM_ACTIVATEAPP:
		if( auto_suspend ){
			if( wparam ){
				if( suspended ) resume();
			}else{
				if( !suspended ) suspend();
			}
		}
		break;
	}

	if( !input || suspended ) return DefWindowProc( hwnd,msg,wparam,lparam );

	if( gfx_mode==3 && use_di ){
		use_di=input->acquire();
		return DefWindowProc( hwnd,msg,wparam,lparam );
	}

	static const int MK_ALLBUTTONS=MK_LBUTTON|MK_RBUTTON|MK_MBUTTON;

	//handle input messages
	switch( msg ){
	case WM_LBUTTONDOWN:
		input->wm_mousedown(1);
		SetCapture(hwnd);
		break;
	case WM_LBUTTONUP:
		input->wm_mouseup(1);
		if( !(wparam&MK_ALLBUTTONS) ) ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
		input->wm_mousedown(2);
		SetCapture( hwnd );
		break;
	case WM_RBUTTONUP:
		input->wm_mouseup(2);
		if( !(wparam&MK_ALLBUTTONS) ) ReleaseCapture();
		break;
	case WM_MBUTTONDOWN:
		input->wm_mousedown(3);
		SetCapture( hwnd );
		break;
	case WM_MBUTTONUP:
		input->wm_mouseup(3);
		if( !(wparam&MK_ALLBUTTONS) ) ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		if( !graphics ) break;
		if( gfx_mode==3 && !use_di ){
			POINT p;GetCursorPos( &p );
			input->wm_mousemove( p.x,p.y );
		}else{
			int x=(short)(lparam&0xffff),y=lparam>>16;
			if( gfx_mode==1 ){
				RECT rect;GetClientRect( hwnd,&rect );
				x=x*graphics->getWidth()/(rect.right-rect.left);
				y=y*graphics->getHeight()/(rect.bottom-rect.top);
			}
			if( x<0 ) x=0;
			else if( x>=graphics->getWidth() ) x=graphics->getWidth()-1;
			if( y<0 ) y=0;
			else if( y>=graphics->getHeight() ) y=graphics->getHeight()-1;
			input->wm_mousemove( x,y );
		}
		break;
	case WM_MOUSEWHEEL:
		input->wm_mousewheel( (short)HIWORD( wparam ) );
		break;
	case WM_KEYDOWN:case WM_SYSKEYDOWN:
		if( lparam & 0x40000000 ) break;
		if( int n=((lparam>>17)&0x80)|((lparam>>16)&0x7f) ) input->wm_keydown( n );
		break;
	case WM_KEYUP:case WM_SYSKEYUP:
		if( int n=((lparam>>17)&0x80)|((lparam>>16)&0x7f) ) input->wm_keyup( n );
		break;
	default:
		return DefWindowProc( hwnd,msg,wparam,lparam );
	}

	return 0;
}

static LRESULT CALLBACK windowProc( HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam ){
	if( runtime ) return runtime->windowProc( hwnd,msg,wparam,lparam );
	return DefWindowProc( hwnd,msg,wparam,lparam );
}*/

//////////////////////////////
//STOP FROM EXTERNAL SOURCE //
//////////////////////////////
void gxRuntime::asyncStop() {
	SDL_Event user_event;
	user_event.type = SDL_USEREVENT;
	user_event.user.windowID = SDL_GetWindowID(window);
	user_event.user.code = WM_STOP;
	user_event.user.data1 = NULL;
	user_event.user.data2 = NULL;
	SDL_PushEvent(&user_event);
}

//////////////////////////////
//RUN  FROM EXTERNAL SOURCE //
//////////////////////////////
void gxRuntime::asyncRun() {
	SDL_Event user_event;
	user_event.type = SDL_USEREVENT;
	user_event.user.windowID = SDL_GetWindowID(window);
	user_event.user.code = WM_RUN;
	user_event.user.data1 = NULL;
	user_event.user.data2 = NULL;
	SDL_PushEvent(&user_event);
}

//////////////////////////////
// END FROM EXTERNAL SOURCE //
//////////////////////////////
void gxRuntime::asyncEnd() {
	SDL_Event user_event;
	user_event.type = SDL_USEREVENT;
	user_event.user.windowID = SDL_GetWindowID(window);
	user_event.user.code = WM_END;
	user_event.user.data1 = NULL;
	user_event.user.data2 = NULL;
	SDL_PushEvent(&user_event);
}

//////////
// IDLE //
//////////
bool gxRuntime::idle() {
	for (;;) {
		SDL_Event event;
		if (suspended && run_flag) {
			SDL_WaitEvent(&event);
		}
		else {
			if (!SDL_PollEvent(&event)) return run_flag;
		}
		if (event.type == SDL_USEREVENT && event.user.windowID == SDL_GetWindowID(window))
		{
			switch (event.user.code) {
			case WM_STOP:
				if (!suspended) forceSuspend();
				break;
			case WM_RUN:
				if (suspended) forceResume();
				break;
			case WM_END:
				run_flag = false;
				break;
			}
		}
	}
	return run_flag;
}

///////////
// DELAY //
///////////
bool gxRuntime::delay(int ms) {
	int t = timeGetTime() + ms;
	for (;;) {
		if (!idle()) RTEX(0); //return false;
		int d = t - timeGetTime();	//how long left to wait
		if (d <= 0) return true;
		if (d > 100) d = 100;
		Sleep(d);
	}
}

///////////////
// DEBUGSTMT //
///////////////
void gxRuntime::debugStmt(int pos, const char* file) {

}

///////////////
// DEBUGSTOP //
///////////////
void gxRuntime::debugStop() {
	if (!suspended) forceSuspend();
}

////////////////
// DEBUGENTER //
////////////////
void gxRuntime::debugEnter(void* frame, void* env, const char* func) {

}

////////////////
// DEBUGLEAVE //
////////////////
void gxRuntime::debugLeave() {

}

////////////////
// DEBUGERROR //
////////////////
void gxRuntime::debugError(const char* t) {
#ifdef _DEBUG
	MessageBox(NULL, t, "DEBUG ERROR", MB_OK | MB_ICONERROR);
	//MessageBox(NULL, t, "Runtime Message", MB_OK | MB_ICONINFORMATION);
	ExitProcess(0);
#endif
}

////////////////
// RUNTIMEERROR //
////////////////
void gxRuntime::runtimeError(const char* t) {
	MessageBox(NULL, t, "RUNTIME ERROR", MB_OK | MB_ICONERROR);
	ExitProcess(0);
}

///////////////
// DEBUGINFO //
///////////////
void gxRuntime::debugInfo(const char* t) {
#ifdef _DEBUG
	//MessageBox(NULL, t, "DEBUG INFO", MB_OK | MB_ICONERROR);
	MessageBox(NULL, t, "Runtime Message", MB_OK | MB_ICONINFORMATION);
#endif
}

//////////////
// DEBUGLOG //
//////////////
void gxRuntime::debugLog(const char* t) {
#ifdef _DEBUG
	MessageBox(NULL, t, "DEBUG LOG", MB_OK | MB_ICONERROR);
#endif
}

/////////////////////////
// RETURN COMMAND LINE //
/////////////////////////
string gxRuntime::commandLine() {
	return cmd_line;
}

/////////////
// EXECUTE //
/////////////
bool gxRuntime::execute(const string& cmd_line) {

	if (!cmd_line.size()) return false;

	//convert cmd_line to cmd and params
	string cmd = cmd_line, params;
	while (cmd.size() && cmd[0] == ' ') cmd = cmd.substr(1);
	if (cmd.find('\"') == 0) {
		int n = cmd.find('\"', 1);
		if (n != string::npos) {
			params = cmd.substr(n + 1);
			cmd = cmd.substr(1, n - 1);
		}
	}
	else {
		int n = cmd.find(' ');
		if (n != string::npos) {
			params = cmd.substr(n + 1);
			cmd = cmd.substr(0, n);
		}
	}
	while (params.size() && params[0] == ' ') params = params.substr(1);
	while (params.size() && params[params.size() - 1] == ' ') params = params.substr(0, params.size() - 1);

	SetForegroundWindow(GetDesktopWindow());

	return (int)ShellExecute(GetDesktopWindow(), 0, cmd.c_str(), params.size() ? params.c_str() : 0, 0, SW_SHOW) > 32;
}

///////////////
// APP TITLE //
///////////////
void gxRuntime::setTitle(const string& t, const string& e) {
	app_title = t;
	app_close = e;
	SDL_SetWindowTitle(window, app_title.c_str());
}

//////////////////
// GETMILLISECS //
//////////////////
int gxRuntime::getMilliSecs() {
	return timeGetTime();
}

/////////////////////
// POINTER VISIBLE //
/////////////////////
void gxRuntime::setPointerVisible(bool vis) {
	if (pointer_visible == vis) return;

	pointer_visible = vis;
	if (gfx_mode == 3) return;

	//force a WM_SETCURSOR
	//POINT pt;
	//GetCursorPos( &pt );
	//SetCursorPos( pt.x,pt.y );

	SDL_ShowCursor(pointer_visible);
}

/////////////////
// AUDIO SETUP //
/////////////////
gxAudio* gxRuntime::openAudio(int flags) {
	if (audio) return 0;

	int f_flags =
		FSOUND_INIT_GLOBALFOCUS |
		FSOUND_INIT_USEDEFAULTMIDISYNTH;

	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(window, &info); // TEMPORARY
	FSOUND_SetHWND(info.info.win.window);
	if (!FSOUND_Init(44100, 1024, f_flags)) {
		return 0;
	}

	audio = d_new gxAudio(this);
	return audio;
}

void gxRuntime::closeAudio(gxAudio* a) {
	if (!audio || audio != a) return;
	delete audio;
	audio = 0;
}

/////////////////
// INPUT SETUP //
/////////////////
gxInput* gxRuntime::openInput(int flags) {
	if (input) return 0;
	IDirectInput7* di;
	if (DirectInputCreateEx(hinst, DIRECTINPUT_VERSION, IID_IDirectInput7, (void**)&di, 0) >= 0) {
		input = d_new gxInput(this, di);
		acquireInput();
	}
	else {
		debugInfo("Create DirectInput failed");
	}
	return input;
}

void gxRuntime::closeInput(gxInput* i) {
	if (!input || input != i) return;
	unacquireInput();
	delete input;
	input = 0;
}

/////////////////////////////////////////////////////
// TIMER CALLBACK FOR AUTOREFRESH OF WINDOWED MODE //
/////////////////////////////////////////////////////
static void CALLBACK timerCallback(UINT id, UINT msg, DWORD_PTR user, DWORD_PTR dw1, DWORD_PTR dw2) {
	if (gfx_mode) {
		gxCanvas* f = runtime->graphics->getFrontCanvas();
		if (f->getModify() != mod_cnt) {
			mod_cnt = f->getModify();
			SDL_SysWMinfo info;
			SDL_VERSION(&info.version);
			SDL_GetWindowWMInfo(runtime->window, &info); // TEMPORARY
			InvalidateRect(info.info.win.window, 0, false);
		}
	}
}

////////////////////
// GRAPHICS SETUP //
////////////////////
void gxRuntime::backupWindowState() {
	SDL_GetWindowPosition(window, &t_x, &t_y);
	SDL_GetWindowSize(window, &t_w, &t_h);
	//t_style=GetWindowLong( hwnd,GWL_STYLE );
}

void gxRuntime::restoreWindowState() {
	//SetWindowLong( hwnd,GWL_STYLE,t_style );
	/*SetWindowPos(
		hwnd,0,t_rect.left,t_rect.top,
		t_rect.right-t_rect.left,t_rect.bottom-t_rect.top,
		SWP_NOZORDER|SWP_FRAMECHANGED );*/
	SDL_SetWindowPosition(window, t_x, t_y);
	SDL_SetWindowSize(window, t_w, t_h);
}

bool gxRuntime::setDisplayMode(int w, int h, int d, int monitor, bool d3d, IDirectDraw7* dirDraw) {

	if (d) return dirDraw->SetDisplayMode(w, h, d, 0, 0) >= 0;

	int best_d = 0;

	if (d3d) {
#ifdef PRO
		int bd = curr_driver->d3d_desc.dwDeviceRenderBitDepth;
		if (bd & DDBD_32) best_d = 32;
		else if (bd & DDBD_24) best_d = 24;
		else if (bd & DDBD_16) best_d = 16;

		is3D = true;
#endif
	}
	else {
		int best_n = 0;
		for (d = 16; d <= 32; d += 8) {
			if (dirDraw->SetDisplayMode(w, h, d, 0, 0) < 0) continue;
			DDCAPS caps = { sizeof(caps) };
			dirDraw->GetCaps(&caps, 0);
			int n = 0;
			if (caps.dwCaps & DDCAPS_BLT) ++n;
			if (caps.dwCaps & DDCAPS_BLTCOLORFILL) ++n;
			if (caps.dwCKeyCaps & DDCKEYCAPS_SRCBLT) ++n;
			if (caps.dwCaps2 & DDCAPS2_WIDESURFACES) ++n;
			if (n == 4)
			{
				is3D = false;
				return true;
			}
			if (n > best_n) {
				best_d = d;
				best_n = n;
			}
			dirDraw->RestoreDisplayMode();
		}
		is3D = false;
	}
	return best_d ? dirDraw->SetDisplayMode(w, h, best_d, 0, 0) >= 0 : false;
}

bool gxRuntime::setDisplayMode(int w, int h, int d, int monitor, int driver, int flags) {
	RTEX("Not Yet Implemented");
	return false;
}

gxGraphics* gxRuntime::openWindowedGraphics(int w, int h, int d, int monitor, bool d3d) {

	IDirectDraw7* dd;
	if (DirectDrawCreateEx(curr_driver->guid, (void**)&dd, IID_IDirectDraw7, 0) < 0) return 0;

	//set coop level
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(window, &info); // TEMPORARY
	HWND hwnd = info.info.win.window;
	if (dd->SetCooperativeLevel(hwnd, DDSCL_NORMAL) >= 0) {
		//create primary surface
		IDirectDrawSurface7* ps;
		DDSURFACEDESC2 desc = { sizeof(desc) };
		desc.dwFlags = DDSD_CAPS;
		desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		if (dd->CreateSurface(&desc, &ps, 0) >= 0) {
			//create clipper
			IDirectDrawClipper* cp;
			if (dd->CreateClipper(0, &cp, 0) >= 0) {
				//attach clipper 
				if (ps->SetClipper(cp) >= 0) {
					//set clipper HWND
					if (cp->SetHWnd(0, hwnd) >= 0) {
						//create front buffer
						IDirectDrawSurface7* fs;
						DDSURFACEDESC2 desc = { sizeof(desc) };
						desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
						desc.dwWidth = w; desc.dwHeight = h;
						desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

						if (d3d) desc.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

						if (dd->CreateSurface(&desc, &fs, 0) >= 0) {
							if (timerID = timeSetEvent(100, 10, timerCallback, 0, TIME_PERIODIC)) {
								//Success!
								clipper = cp;
								primSurf = ps;
								mod_cnt = 0;
								fs->AddRef();
								return d_new gxGraphics(this, dd, fs, fs, d3d);
							}
							fs->Release();
						}
					}
				}
				cp->Release();
			}
			ps->Release();
		}
	}
	dd->Release();
	return 0;
}

gxGraphics* gxRuntime::openExclusiveGraphics(int w, int h, int d, int monitor, bool d3d) {

	IDirectDraw7* dd;
	if (DirectDrawCreateEx(curr_driver->guid, (void**)&dd, IID_IDirectDraw7, 0) < 0) return 0;

	//Set coop level
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(window, &info); // TEMPORARY
	HWND hwnd = info.info.win.window;
	if (dd->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT) >= 0) {
		//Set display mode
		if (setDisplayMode(w, h, d, monitor, d3d, dd)) {
			//create primary surface
			IDirectDrawSurface7* ps;
			DDSURFACEDESC2 desc = { sizeof(desc) };
			desc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
			desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;

			desc.dwBackBufferCount = 1;
			if (d3d) desc.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

			if (dd->CreateSurface(&desc, &ps, 0) >= 0) {
				//find back surface
				IDirectDrawSurface7* bs;
				DDSCAPS2 caps = { sizeof caps };
				caps.dwCaps = DDSCAPS_BACKBUFFER;
				if (ps->GetAttachedSurface(&caps, &bs) >= 0) {
					return d_new gxGraphics(this, dd, ps, bs, d3d);
				}
				ps->Release();
			}
			dd->RestoreDisplayMode();
		}
	}
	dd->Release();
	return 0;
}

gxGraphics* gxRuntime::openGraphics(int w, int h, int d, int monitor, int driver, int flags) {
	if (graphics) return 0;

	busy = true;

	bool d3d = flags & gxGraphics::GRAPHICS_3D ? true : false;
	bool windowed = flags & gxGraphics::GRAPHICS_WINDOWED ? true : false;

	if (windowed) driver = 0;

	curr_driver = drivers[driver];

	if (windowed) {
		if ((graphics = openWindowedGraphics(w, h, d, monitor, d3d))) {
			gfx_mode = (flags & gxGraphics::GRAPHICS_SCALED) ? 1 : 2;
			auto_suspend = (flags & gxGraphics::GRAPHICS_AUTOSUSPEND) != 0;
			int ws, ww, hh;
			if (gfx_mode == 1) {
				ws = scaled_ws;
				SDL_GetWindowSize(window, &ww, &hh);
				/*RECT c_r;
				GetClientRect( hwnd,&c_r );
				ww=c_r.right-c_r.left;
				hh=c_r.bottom-c_r.top;*/
			}
			else {
				ws = static_ws;
				ww = w;
				hh = h;
			}

			if (gfx_mode == 1)
			{
				SDL_SetWindowResizable(window, SDL_FALSE);
				SDL_SetWindowBordered(window, SDL_FALSE);
				SDL_Rect bounds;
				SDL_GetDisplayBounds(monitor, &bounds);
				SDL_SetWindowPosition(window, bounds.x, bounds.y);
				SDL_SetWindowSize(window, bounds.w, bounds.h);
			}
			else
			{
				SDL_SetWindowSize(window, ww, hh);
				SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(monitor), SDL_WINDOWPOS_CENTERED_DISPLAY(monitor));
				//SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}

			//SetWindowLong( hwnd,GWL_STYLE,ws );
			//SetWindowPos( hwnd,0,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED );


			/*RECT w_r,c_r;
			GetWindowRect( hwnd,&w_r );
			GetClientRect( hwnd,&c_r );
			int tw=(w_r.right-w_r.left)-(c_r.right-c_r.left);
			int th=(w_r.bottom-w_r.top)-(c_r.bottom-c_r.top );
			int cx=( GetSystemMetrics( SM_CXSCREEN )-ww )/2;
			int cy=( GetSystemMetrics( SM_CYSCREEN )-hh )/2;
			POINT zz={0,0};
			ClientToScreen( hwnd,&zz );
			int bw=zz.x-w_r.left,bh=zz.y-w_r.top;
			int wx=cx-bw,wy=cy-bh;if( wy<0 ) wy=0;		//not above top!
			MoveWindow( hwnd,wx,wy,ww+tw,hh+th,true );*/

			//int display = 2;

			//SDL_SetWindowSize(window, ww, hh);
			//SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(display), SDL_WINDOWPOS_CENTERED_DISPLAY(display));
			//SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		}
	}
	else {
		backupWindowState();

		//SetWindowLong( hwnd,GWL_STYLE,WS_VISIBLE|WS_POPUP );
		//SetWindowPos( hwnd,0,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED );
		int display = 0;
		//SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(display), SDL_WINDOWPOS_CENTERED_DISPLAY(display));
		//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

		SDL_SetWindowResizable(window, SDL_FALSE);
		SDL_SetWindowBordered(window, SDL_FALSE);
		SDL_Rect bounds;
		SDL_GetDisplayBounds(display, &bounds);
		SDL_SetWindowPosition(window, bounds.x, bounds.y);
		SDL_SetWindowSize(window, bounds.w, bounds.h);

		ShowCursor(0);
		if (graphics = openExclusiveGraphics(w, h, d, monitor, d3d)) {
			gfx_mode = 3;
			auto_suspend = true;
			SetCursorPos(0, 0);
			acquireInput();
		}
		else {
			ShowCursor(1);
			restoreWindowState();
		}

	}

	if (!graphics) curr_driver = 0;

	gfx_lost = false;
	is_focused = true;

	busy = false;

	return graphics;
}

void gxRuntime::closeGraphics(gxGraphics* g) {
	if (!graphics || graphics != g) return;

	auto_suspend = false;

	is_focused = false;

	busy = true;

	unacquireInput();
	if (timerID) { timeKillEvent(timerID); timerID = 0; }
	if (clipper) { clipper->Release(); clipper = 0; }
	if (primSurf) { primSurf->Release(); primSurf = 0; }
	delete graphics; graphics = 0;

	if (gfx_mode == 3) {
		ShowCursor(1);
		restoreWindowState();
	}
	gfx_mode = 0;

	gfx_lost = false;

	busy = false;
}

bool gxRuntime::graphicsLost() {
	return gfx_lost;
}

bool gxRuntime::isFocused()
{
	return is_focused;
}

gxFileSystem* gxRuntime::openFileSystem(int flags) {
	if (fileSystem) return 0;

	fileSystem = d_new gxFileSystem();
	return fileSystem;
}

void gxRuntime::closeFileSystem(gxFileSystem* f) {
	if (!fileSystem || fileSystem != f) return;

	delete fileSystem;
	fileSystem = 0;
}

////////////////////
// GFX ENUM STUFF //
////////////////////
static HRESULT WINAPI enumMode(DDSURFACEDESC2* desc, void* context) {
	int dp = desc->ddpfPixelFormat.dwRGBBitCount;
	if (dp == 16 || dp == 24 || dp == 32) {
		gxRuntime::GfxMode* m = d_new gxRuntime::GfxMode;
		m->desc = *desc;
		gxRuntime::GfxDriver* d = (gxRuntime::GfxDriver*)context;
		d->modes.push_back(m);
	}
	return DDENUMRET_OK;
}

#ifdef PRO
static int maxDevType;
static HRESULT CALLBACK enumDevice(char* desc, char* name, D3DDEVICEDESC7* devDesc, void* context) {
	int t = 0;
	GUID guid = devDesc->deviceGUID;
	if (guid == IID_IDirect3DRGBDevice) t = 1;
	else if (guid == IID_IDirect3DHALDevice) t = 2;
	else if (guid == IID_IDirect3DTnLHalDevice) t = 3;
	if (t > 1 && t > maxDevType) {
		maxDevType = t;
		gxRuntime::GfxDriver* d = (gxRuntime::GfxDriver*)context;
		d->d3d_desc = *devDesc;
	}
	return D3DENUMRET_OK;
}
#endif

static BOOL WINAPI enumDriver(GUID FAR* guid, LPSTR desc, LPSTR name, LPVOID context, HMONITOR hm) {
	IDirectDraw7* dd;
	if (DirectDrawCreateEx(guid, (void**)&dd, IID_IDirectDraw7, 0) < 0) return 0;

	if (!guid && !desktop_desc.ddpfPixelFormat.dwRGBBitCount) {
		desktop_desc.dwSize = sizeof(desktop_desc);
		dd->GetDisplayMode(&desktop_desc);
	}

	gxRuntime::GfxDriver* d = d_new gxRuntime::GfxDriver;

	d->guid = guid ? d_new GUID(*guid) : 0;
	d->name = desc;//string( name )+" "+string( desc );

#ifdef PRO
	memset(&d->d3d_desc, 0, sizeof(d->d3d_desc));
	IDirect3D7* dir3d;
	if (dd->QueryInterface(IID_IDirect3D7, (void**)&dir3d) >= 0) {
		maxDevType = 0;
		dir3d->EnumDevices(enumDevice, d);
		dir3d->Release();
	}
#endif
	vector<gxRuntime::GfxDriver*>* drivers = (vector<gxRuntime::GfxDriver*>*)context;
	drivers->push_back(d);
	dd->EnumDisplayModes(0, 0, d, enumMode);
	dd->Release();
	return 1;
}

void gxRuntime::enumGfx() {
	denumGfx();
	if (enum_all) {
		DirectDrawEnumerateEx(enumDriver, &drivers, DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES);
	}
	else {
		DirectDrawEnumerateEx(enumDriver, &drivers, 0);
	}
}

void gxRuntime::denumGfx() {
	for (int k = 0; k < (int)drivers.size(); ++k) {
		gxRuntime::GfxDriver* d = drivers[k];
		for (int j = 0; j < (int)d->modes.size(); ++j) delete d->modes[j];
		delete d->guid;
		delete d;
	}
	drivers.clear();
}

int gxRuntime::numGraphicsDrivers() {
	if (!enum_all) {
		enum_all = true;
		enumGfx();
	}
	return drivers.size();
}

void gxRuntime::graphicsDriverInfo(int driver, string* name, int* c) {
	GfxDriver* g = drivers[driver];
	int caps = 0;
#ifdef PRO
	if (g->d3d_desc.dwDeviceRenderBitDepth) caps |= GFXMODECAPS_3D;
#endif
	* name = g->name;
	*c = caps;
}

int gxRuntime::numGraphicsModes(int driver) {
	return drivers[driver]->modes.size();
}

void gxRuntime::graphicsModeInfo(int driver, int mode, int* w, int* h, int* d, int* c) {
	GfxDriver* g = drivers[driver];
	GfxMode* m = g->modes[mode];
	int caps = 0;
#ifdef PRO
	int bd = 0;
	switch (m->desc.ddpfPixelFormat.dwRGBBitCount) {
	case 16:bd = DDBD_16; break;
	case 24:bd = DDBD_24; break;
	case 32:bd = DDBD_32; break;
	}
	if (g->d3d_desc.dwDeviceRenderBitDepth & bd) caps |= GFXMODECAPS_3D;
#endif
	* w = m->desc.dwWidth;
	*h = m->desc.dwHeight;
	*d = m->desc.ddpfPixelFormat.dwRGBBitCount;
	*c = caps;
}

void gxRuntime::windowedModeInfo(int* c) {
	int caps = 0;
#ifdef PRO
	int bd = 0;
	switch (desktop_desc.ddpfPixelFormat.dwRGBBitCount) {
	case 16:bd = DDBD_16; break;
	case 24:bd = DDBD_24; break;
	case 32:bd = DDBD_32; break;
	}
	if (drivers[0]->d3d_desc.dwDeviceRenderBitDepth & bd) caps |= GFXMODECAPS_3D;
#endif
	* c = caps;
}

gxTimer* gxRuntime::createTimer(int hertz) {
	gxTimer* t = d_new gxTimer(this, hertz);
	timers.insert(t);
	return t;
}

void gxRuntime::freeTimer(gxTimer* t) {
	if (!timers.count(t)) return;
	timers.erase(t);
	delete t;
}

static string toDir(string t) {
	if (t.size() && t[t.size() - 1] != '\\') t += '\\';
	return t;
}

string gxRuntime::systemProperty(const std::string& p) {
	char buff[MAX_PATH + 1];
	string t = tolower(p);
	if (t == "cpu") {
		return "Intel";
	}
	else if (t == "os") {
		/*switch (osinfo.dwMajorVersion) {
		case 3:
			switch (osinfo.dwMinorVersion) {
			case 51:return "Windows NT 3.1";
			}
			break;
		case 4:
			switch (osinfo.dwMinorVersion) {
			case 0:return "Windows 95";
			case 10:return "Windows 98";
			case 90:return "Windows ME";
			}
			break;
		case 5:
			switch (osinfo.dwMinorVersion) {
			case 0:return "Windows 2000";
			case 1:return "Windows XP";
			case 2:return "Windows Server 2003";
			}
			break;
		case 6:
			switch (osinfo.dwMinorVersion) {
			case 0:return "Windows Vista";
			case 1:return "Windows 7";
			}
			break;
		}*/

		char osVersion[2048];
		if(GetOSVersionString(osVersion, 2048))
			return osVersion;
	}
	else if (t == "appdir") {
		if (GetModuleFileName(0, buff, MAX_PATH)) {
			string t = buff;
			int n = t.find_last_of('\\');
			if (n != string::npos) t = t.substr(0, n);
			return toDir(t);
		}
	}
	else if (t == "apphwnd") {
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		SDL_GetWindowWMInfo(window, &info); // TEMPORARY
		return itoa((int)info.info.win.window);
	}
	else if (t == "apphinstance") {
		return itoa((int)hinst);
	}
	else if (t == "windowsdir") {
		if (GetWindowsDirectory(buff, MAX_PATH)) return toDir(buff);
	}
	else if (t == "systemdir") {
		if (GetSystemDirectory(buff, MAX_PATH)) return toDir(buff);
	}
	else if (t == "tempdir") {
		if (GetTempPath(MAX_PATH, buff)) return toDir(buff);
	}
	else if (t == "direct3d7") {
		if (graphics) return itoa((int)graphics->dir3d);
	}
	else if (t == "direct3ddevice7") {
		if (graphics) return itoa((int)graphics->dir3dDev);
	}
	else if (t == "directdraw7") {
		if (graphics) return itoa((int)graphics->dirDraw);
	}
	else if (t == "directinput7") {
		if (input) return itoa((int)input->dirInput);
	}
	return "";
}

void gxRuntime::enableDirectInput(bool enable) {
	if (use_di = enable) {
		acquireInput();
	}
	else {
		unacquireInput();
	}
}
