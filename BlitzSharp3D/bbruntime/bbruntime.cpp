
#include "std.h"
#include "bbsys.h"
#include "bbruntime.h"

bool _restartGame = false;

void bbRestart()
{
	_restartGame = true;
	RTEX(0);
}

void  bbEnd() {
	RTEX(0);
}
void  bbStop() {
	gx_runtime->debugStop();
	if (!gx_runtime->idle()) RTEX(0);
}

void  bbAppTitle(BBStr* ti, BBStr* cp) {
	gx_runtime->setTitle(*ti, *cp);
	delete ti; delete cp;
}

void  bbRuntimeError(BBStr* str) {
	string t = *str; delete str;
	/*if( t.size()>8192 ) t[8192]=0;
	static char err[8192];
	strcpy_s(err, 8192,t.c_str() );
	RTEXR( err );*/

	// No need to make a copy of the string in this case
	RTEXR(t.c_str());
}

BBStr* bbGetBuildType()
{
#ifdef _DEBUG
	const char* type = "Debug";
#else
	const char* type = "Release";
#endif
	return d_new BBStr(type);
}

int   bbExecFile(BBStr* f) {
	string t = *f; delete f;
	int n = gx_runtime->execute(t);
	if (!gx_runtime->idle()) RTEX(0);
	return n;
}

void  bbDelay(int ms) {
	if (!gx_runtime->delay(ms)) RTEX(0);
}

int  bbMilliSecs() {
	return gx_runtime->getMilliSecs();
}

BBStr* bbCommandLine() {
	return d_new BBStr(gx_runtime->commandLine());
}

BBStr* bbSystemProperty(BBStr* p) {
	string t = gx_runtime->systemProperty(*p);
	delete p; return d_new BBStr(t);
}

BBStr* bbGetEnv(BBStr* env_var) {

	char* p = NULL;
	size_t sz;
	errno_t err = _dupenv_s(&p, &sz, env_var->c_str());


	//char *p=getenv( env_var->c_str() );
	BBStr* val = d_new BBStr(p ? p : "");
	delete env_var;
	return val;
}

void  bbSetEnv(BBStr* env_var, BBStr* val) {
	string t = *env_var + "=" + *val;
	_putenv(t.c_str());
	delete env_var;
	delete val;
}

gxTimer* bbCreateTimer(int hertz) {
	gxTimer* t = gx_runtime->createTimer(hertz);
	return t;
}

int   bbWaitTimer(gxTimer* t) {
	int n = t->wait();
	if (!gx_runtime->idle()) RTEX(0);
	return n;
}

void  bbFreeTimer(gxTimer* t) {
	gx_runtime->freeTimer(t);
}

void  bbDebugLog(BBStr* t) {
	gx_runtime->debugLog(t->c_str());
	delete t;
}

void  _bbDebugStmt(int pos, const char* file) {
	gx_runtime->debugStmt(pos, file);
	if (!gx_runtime->idle()) RTEX(0);
}

void  _bbDebugEnter(void* frame, void* env, const char* func) {
	gx_runtime->debugEnter(frame, env, func);
}

void  _bbDebugLeave() {
	gx_runtime->debugLeave();
}

bool basic_create();
bool basic_destroy();
void basic_link(void (*rtSym)(const char* sym, void* pc));
bool graphics_create();
bool graphics_destroy();
void graphics_link(void (*rtSym)(const char* sym, void* pc));
bool input_create();
bool input_destroy();
void input_link(void (*rtSym)(const char* sym, void* pc));
bool audio_create();
bool audio_destroy();
void audio_link(void (*rtSym)(const char* sym, void* pc));
#ifdef PRO
bool blitz3d_create();
bool blitz3d_destroy();
void blitz3d_link(void (*rtSym)(const char* sym, void* pc));
#else
bool blitz3d_create() { return true; }
bool blitz3d_destroy() { return true; }
void blitz3d_link(void (*rtSym)(const char* sym, void* pc)) {}
#endif

void bbruntime_link(void (*rtSym)(const char* sym, void* pc)) {

	rtSym("Restart", bbRestart);
	rtSym("End", bbEnd);
	rtSym("Stop", bbStop);
	rtSym("AppTitle$title$close_prompt=\"\"", bbAppTitle);
	rtSym("RuntimeError$message", bbRuntimeError);
	rtSym("ExecFile$command", bbExecFile);
	rtSym("Delay%millisecs", bbDelay);
	rtSym("%MilliSecs", bbMilliSecs);
	rtSym("$CommandLine", bbCommandLine);
	rtSym("$SystemProperty$property", bbSystemProperty);
	rtSym("$GetEnv$env_var", bbGetEnv);
	rtSym("SetEnv$env_var$value", bbSetEnv);

	rtSym("%CreateTimer%hertz", bbCreateTimer);
	rtSym("%WaitTimer%timer", bbWaitTimer);
	rtSym("FreeTimer%timer", bbFreeTimer);
	rtSym("DebugLog$text", bbDebugLog);

	rtSym("_bbDebugStmt", _bbDebugStmt);
	rtSym("_bbDebugEnter", _bbDebugEnter);
	rtSym("_bbDebugLeave", _bbDebugLeave);

	basic_link(rtSym);
	graphics_link(rtSym);
	input_link(rtSym);
	audio_link(rtSym);
	blitz3d_link(rtSym);
}

//start up error
static void sue(const char* t) {
	string p = string("Startup Error: ") + t;
	gx_runtime->debugInfo(p.c_str());
}

bool bbruntime_create() {
	if (basic_create()) {
								if (graphics_create()) {
									if (input_create()) {
										if (audio_create()) {
												if (blitz3d_create()) {
														return true;
												}
												else sue("blitz3d_create failed");
											audio_destroy();
										}
										else sue("audio_create failed");
										input_destroy();
									}
									else sue("input_create failed");
									graphics_destroy();
								}
								else sue("graphics_create failed");
		basic_destroy();
	}
	else sue("basic_create failed");
	return false;
}

bool bbruntime_destroy() {
	blitz3d_destroy();
	audio_destroy();
	input_destroy();
	graphics_destroy();
	basic_destroy();
	return true;
}

extern "C" __declspec(dllexport) bool InitBlitz() {
	HINSTANCE hInst = GetModuleHandle(nullptr);
	const string cmdLine = "";
	gx_runtime = gxRuntime::openRuntime(hInst, cmdLine);

	return bbruntime_create();
}

extern "C" __declspec(dllexport) bool CloseBlitz() {
	return bbruntime_destroy();
}

void bbruntime_panic(const char* err) {
	RTEX(err);
}
