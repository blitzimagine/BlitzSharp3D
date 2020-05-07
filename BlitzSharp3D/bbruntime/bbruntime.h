
/*

Platform neutral runtime library.

To be statically linked with an appropriate gxruntime driver.

*/

#ifndef BBRUNTIME_H
#define BBRUNTIME_H

#include "std.h"
#include "bbsys.h"
#include "../gxruntime/gxruntime.h"

void bbruntime_link(void (*rtSym)(const char* sym, void* pc));

const char* bbruntime_run(gxRuntime* runtime, void (*pc)());

void bbruntime_panic(const char* err);

void bbRestart();
void bbEnd();
void bbStop();
void bbAppTitle(BBStr* ti, BBStr* cp);
void bbRuntimeError(BBStr* str);
BBStr* bbGetBuildType();
int bbExecFile(BBStr* f);
void bbDelay(int ms);
int bbMilliSecs();
BBStr* bbCommandLine();
BBStr* bbSystemProperty(BBStr* p);
BBStr* bbGetEnv(BBStr* env_var);
void bbSetEnv(BBStr* env_var, BBStr* val);
gxTimer* bbCreateTimer(int hertz);
int bbWaitTimer(gxTimer* t);
void bbFreeTimer(gxTimer* t);
void bbDebugLog(BBStr* t);

extern bool _restartGame;

#endif
