#include "monoutil.h"

#include "../bbruntime/bbstring.h"

BBStr* toBBStr(const char* str)
{
	return _bbStrConst(str);
}

void freeBBStr(BBStr* str)
{
	_bbStrRelease(str);
}

const char* toMonoStrNoFree(BBStr* str)
{
	char* ret = static_cast<char*>(malloc(str->length() + 1));
	if (ret == nullptr)
		return nullptr;
	errno_t err = strcpy_s(ret, str->length(), str->c_str());
	if (ret != nullptr)
		ret[str->length()] = 0;
	return ret;
}

const char* toMonoStr(BBStr* str)
{
	const char* ret = toMonoStrNoFree(str);
	freeBBStr(str);
	return ret;
}
