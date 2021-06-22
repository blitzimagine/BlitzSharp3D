#pragma once

#ifdef _WIN32
#define PUBLIC_METHOD extern "C" __declspec(dllexport)
#else
#define PUBLIC_METHOD extern "C"
#endif

struct BBStr;

extern BBStr* toBBStr(const char* str);
extern void freeBBStr(BBStr* str);
extern const char* toMonoStrNoFree(BBStr* str);
extern const char* toMonoStr(BBStr* str);
