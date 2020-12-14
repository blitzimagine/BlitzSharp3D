#pragma once

#include <windows.h>
#include <stdint.h>

extern bool GetOSVersionStringW(WCHAR* version, size_t maxlen);
extern bool GetOSVersionStringA(char* version, size_t maxlen);

#ifdef UNICODE
#define GetOSVersionString GetOSVersionStringW
#else
#define GetOSVersionString GetOSVersionStringA
#endif // !UNICODE
