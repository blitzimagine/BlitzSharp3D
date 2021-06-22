#include "monoutil.h"
#include "../bbruntime/bbfilesystem.h"

PUBLIC_METHOD int Eof_internal(bbStream* stream)
{
	return bbEof(stream) != 0;
}

PUBLIC_METHOD int ReadAvail_internal(bbStream* stream)
{
	return bbReadAvail(stream);
}

PUBLIC_METHOD char ReadByte_internal(bbStream* stream)
{
	return (char)bbReadByte(stream);
}

PUBLIC_METHOD short ReadShort_internal(bbStream* stream)
{
	return (short)bbReadShort(stream);
}

PUBLIC_METHOD int ReadInt_internal(bbStream* stream)
{
	return bbReadInt(stream);
}

PUBLIC_METHOD float ReadFloat_internal(bbStream* stream)
{
	return bbReadFloat(stream);
}

PUBLIC_METHOD void ReadString_internal(char* ret, int retLen, bbStream* stream)
{
	BBStr* str = bbReadString(stream);
	strcpy_s(ret, retLen, str->c_str());
	freeBBStr(str);
}

PUBLIC_METHOD void ReadLine_internal(char* ret, int retLen, bbStream* stream)
{
	BBStr* str = bbReadLine(stream);
	strcpy_s(ret, retLen, str->c_str());
	freeBBStr(str);
}

PUBLIC_METHOD void WriteByte_internal(bbStream* stream, char n)
{
	bbWriteByte(stream, (int)n);
}

PUBLIC_METHOD void WriteShort_internal(bbStream* stream, short n)
{
	bbWriteShort(stream, (int)n);
}

PUBLIC_METHOD void WriteInt_internal(bbStream* stream, int n)
{
	bbWriteInt(stream, n);
}

PUBLIC_METHOD void WriteFloat_internal(bbStream* stream, float n)
{
	bbWriteFloat(stream, n);
}

PUBLIC_METHOD void WriteString_internal(bbStream* stream, const char* string)
{
	BBStr* s = toBBStr(string);
	bbWriteString(stream, s);
	freeBBStr(s);
}

PUBLIC_METHOD void WriteLine_internal(bbStream* stream, const char* string)
{
	BBStr* s = toBBStr(string);
	bbWriteLine(stream, s);
	freeBBStr(s);
}

PUBLIC_METHOD void CopyStream_internal(bbStream* src, bbStream* dest, const int bufferSize)
{
	bbCopyStream(src, dest, bufferSize);
}