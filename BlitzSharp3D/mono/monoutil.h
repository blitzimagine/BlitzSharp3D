#pragma once

#include "../bbruntime/bbstring.h"

extern BBStr* toBBStr(const char* str);
extern void freeBBStr(BBStr* str);
extern const char* toMonoStrNoFree(BBStr* str);
extern const char* toMonoStr(BBStr* str);
