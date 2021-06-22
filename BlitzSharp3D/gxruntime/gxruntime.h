
#ifndef GXRUNTIME_H
#define GXRUNTIME_H

#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>

#include "gxaudio.h"
#include "gxinput.h"
#include "gxgraphics.h"
#include "gxfilesystem.h"
#include "gxtimer.h"

class gxRuntime {
	/***** INTERNAL INTERFACE *****/
public:

	SDL_Window* window;
	//HWND hwnd;
	HINSTANCE hinst;

	gxAudio* audio;
	gxInput* input;
	gxGraphics* graphics;
	gxFileSystem* fileSystem;

	bool is3D;

	void flip(bool vwait);
	void moveMouse(int x, int y);

	int eventProc(void* userdata, SDL_Event* event);
	//LRESULT windowProc( HWND hwnd,UINT msg,WPARAM w,LPARAM l );

	struct GfxMode;
	struct GfxDriver;

private:
	gxRuntime(HINSTANCE hinst, const std::string& cmd_line, SDL_Window* window);
	gxRuntime();
	~gxRuntime();

	void paint();
	void suspend();
	void forceSuspend();
	void resume();
	void forceResume();
	void backupWindowState();
	void restoreWindowState();

	int t_x, t_y, t_w, t_h;
	int t_style;
	std::string cmd_line;
	bool pointer_visible;
	std::string app_title;
	std::string app_close;
	gxGraphics* openWindowedGraphics(int w, int h, int d, int monitor, bool d3d);
	gxGraphics* openExclusiveGraphics(int w, int h, int d, int monitor, bool d3d);

	bool enum_all;
	std::vector<GfxDriver*> drivers;
	GfxDriver* curr_driver;
	int use_di;

	void enumGfx();
	void denumGfx();

	void resetInput();
	void pauseAudio();
	void resumeAudio();
	void backupGraphics();
	void restoreGraphics();
	void acquireInput();
	void unacquireInput();

	/***** APP INTERFACE *****/
public:
	static gxRuntime* openRuntime(HINSTANCE hinst, const std::string& cmd_line);
	static void closeRuntime(gxRuntime* runtime);

	bool setDisplayMode(int w, int h, int d, int monitor, bool d3d, IDirectDraw7* dd);
	bool setDisplayMode(int w, int h, int d, int monitor, int driver, int flags);

	void asyncStop();
	void asyncRun();
	void asyncEnd();

	/***** GX INTERFACE *****/
public:
	enum {
		GFXMODECAPS_3D = 1
	};

	//return true if program should continue, or false for quit.
	bool idle();
	bool delay(int ms);

	bool execute(const std::string& cmd);
	void setTitle(const std::string& title, const std::string& close);
	int  getMilliSecs();
	void setPointerVisible(bool vis);

	std::string commandLine();

	std::string systemProperty(const std::string& t);

	void debugStop();
	void debugProfile(int per);
	void debugStmt(int pos, const char* file);
	void debugEnter(void* frame, void* env, const char* func);
	void debugLeave();
	static void debugInfo(const char* t);
	static void debugError(const char* t);
	static void runtimeError(const char* t);
	static void debugLog(const char* t);

	int numGraphicsDrivers();
	void graphicsDriverInfo(int driver, std::string* name, int* caps);

	int numGraphicsModes(int driver);
	void graphicsModeInfo(int driver, int mode, int* w, int* h, int* d, int* caps);

	void windowedModeInfo(int* caps);

	gxAudio* openAudio(int flags);
	void closeAudio(gxAudio* audio);

	gxInput* openInput(int flags);
	void closeInput(gxInput* input);

	gxGraphics* openGraphics(int w, int h, int d, int monitor, int driver, int flags);
	void closeGraphics(gxGraphics* graphics);
	bool graphicsLost();

	bool isFocused();

	gxFileSystem* openFileSystem(int flags);
	void closeFileSystem(gxFileSystem* filesys);

	gxTimer* createTimer(int hertz);
	void freeTimer(gxTimer* timer);

	void enableDirectInput(bool use);
	int  directInputEnabled() { return use_di; }

	//OSVERSIONINFO osinfo;
};

#endif