#include "monoutil.h"
#include "../bbruntime/bbstring.h"

PUBLIC_METHOD void Left_internal(char* ret, int retLen, const char* str, int length)
{
	BBStr* s = toBBStr(str);
	strcpy_s(ret, retLen, toMonoStr(bbLeft(s, length)));
	freeBBStr(s);
}

PUBLIC_METHOD void Right_internal(char* ret, int retLen, const char* str, int length)
{
	BBStr* s = toBBStr(str);
	strcpy_s(ret, retLen, toMonoStr(bbRight(s, length)));
	freeBBStr(s);
}

PUBLIC_METHOD void Mid_internal(char* ret, int retLen, const char* str, int offset, int length)
{
	BBStr* s = toBBStr(str);
	strcpy_s(ret, retLen, toMonoStr(bbMid(s, offset, length)));
	freeBBStr(s);
}

PUBLIC_METHOD int Instr(const char* str1, const char* str2, int offset)
{
	BBStr* s1 = toBBStr(str1);
	BBStr* s2 = toBBStr(str2);
	int ret = bbInstr(s1, s2, offset);
	freeBBStr(s1);
	freeBBStr(s2);

	return ret;
}