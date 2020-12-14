#include "monoutil.h"

#include "../bbruntime/bbruntime.h"

PUBLIC_METHOD void RuntimeStats()
{
	bbRuntimeStats();
}

PUBLIC_METHOD void Restart()
{
	bbRestart();
}

PUBLIC_METHOD void End()
{
	bbEnd();
}

PUBLIC_METHOD void Stop()
{
	bbStop();
}

PUBLIC_METHOD void AppTitle(const char* title, const char* closePrompt)
{
	BBStr* ti = toBBStr(title);
	BBStr* cp = toBBStr(closePrompt);
	bbAppTitle(ti, cp);
	freeBBStr(ti);
	freeBBStr(cp);
}

PUBLIC_METHOD void RuntimeError(const char* message)
{
	BBStr* msg = toBBStr(message);
	bbRuntimeError(msg);
	freeBBStr(msg);
}

PUBLIC_METHOD int ExecFile(const char* command)
{
	BBStr* cmd = toBBStr(command);
	int ret = bbExecFile(cmd);
	freeBBStr(cmd);
	return ret;
}

PUBLIC_METHOD void Delay(int millisecs)
{
	bbDelay(millisecs);
}

PUBLIC_METHOD int MilliSecs()
{
	return bbMilliSecs();
}

PUBLIC_METHOD void CommandLine_internal(char* ret, int retLen)
{
	BBStr* str = bbCommandLine();
	strcpy_s(ret, retLen, str->c_str());
	freeBBStr(str);
}

PUBLIC_METHOD void SystemProperty_internal(char* ret, int retLen, const char* prop)
{
	BBStr* p = toBBStr(prop);
	strcpy_s(ret, retLen, bbSystemProperty(p)->c_str());
	freeBBStr(p);
}

PUBLIC_METHOD void GetEnv_internal(char* ret, int retLen, const char* env_var)
{
	BBStr* v = toBBStr(env_var);
	strcpy_s(ret, retLen, bbGetEnv(v)->c_str());
	freeBBStr(v);
}

PUBLIC_METHOD void SetEnv(const char* env_var, const char* val)
{
	BBStr* env = toBBStr(env_var);
	BBStr* v = toBBStr(val);
	bbSetEnv(env, v);
	freeBBStr(env);
	freeBBStr(v);
}

PUBLIC_METHOD gxTimer* CreateTimer_internal(int hertz)
{
	return bbCreateTimer(hertz);
}

PUBLIC_METHOD int WaitTimer_internal(gxTimer* timer)
{
	return bbWaitTimer(timer);
}

PUBLIC_METHOD void FreeTimer_internal(gxTimer* timer)
{
	bbFreeTimer(timer);
}

PUBLIC_METHOD void DebugLog(const char* text)
{
	BBStr* txt = toBBStr(text);
	bbDebugLog(txt);
	freeBBStr(txt);
}