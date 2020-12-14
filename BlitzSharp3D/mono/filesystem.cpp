#include "monoutil.h"
#include "../bbruntime/bbfilesystem.h"

PUBLIC_METHOD bbFile* OpenFile_internal(const char* filename)
{
	BBStr* fn = toBBStr(filename);
	bbFile* ret = bbOpenFile(fn);
	freeBBStr(fn);
	return ret;
}

PUBLIC_METHOD bbFile* ReadFile_internal(const char* filename)
{
	BBStr* fn = toBBStr(filename);
	bbFile* ret = bbReadFile(fn);
	freeBBStr(fn);
	return ret;
}

PUBLIC_METHOD bbFile* WriteFile_internal(const char* filename)
{
	BBStr* fn = toBBStr(filename);
	bbFile* ret = bbWriteFile(fn);
	freeBBStr(fn);
	return ret;
}

PUBLIC_METHOD void CloseFile_internal(bbFile* file)
{
	bbCloseFile(file);
}

PUBLIC_METHOD int FilePos_internal(bbFile* file)
{
	return bbFilePos(file);
}

PUBLIC_METHOD int SeekFile_internal(bbFile* file, int pos)
{
	return bbSeekFile(file, pos);
}

PUBLIC_METHOD gxDir* ReadDir_internal(const char* dirname)
{
	if (dirname == nullptr || strlen(dirname) == 0)
		return nullptr;
	BBStr* dir = toBBStr(dirname);
	gxDir* ret = bbReadDir(dir);
	freeBBStr(dir);
	return ret;
}

PUBLIC_METHOD void CloseDir_internal(gxDir* dir)
{
	bbCloseDir(dir);
}

PUBLIC_METHOD void NextFile_internal(char* ret, int retLen, gxDir* dir)
{
	BBStr* f = bbNextFile(dir);
	strcpy_s(ret, retLen, f->c_str());
	freeBBStr(f);
}

PUBLIC_METHOD void CurrentDir_internal(char* ret, int retLen)
{
	BBStr* currentDir = bbCurrentDir();
	strcpy_s(ret, retLen, currentDir->c_str());
	freeBBStr(currentDir);
}

PUBLIC_METHOD void ChangeDir(const char* dir)
{
	BBStr* d = toBBStr(dir);
	bbChangeDir(d);
	freeBBStr(d);
}

PUBLIC_METHOD void CreateDir(const char* dir)
{
	BBStr* d = toBBStr(dir);
	bbCreateDir(d);
	freeBBStr(d);
}

PUBLIC_METHOD void DeleteDir(const char* dir)
{
	BBStr* d = toBBStr(dir);
	bbDeleteDir(d);
	freeBBStr(d);
}

PUBLIC_METHOD int FileSize(const char* file)
{
	BBStr* f = toBBStr(file);
	int ret = bbFileSize(f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD int FileType(const char* file)
{
	BBStr* f = toBBStr(file);
	int ret = bbFileType(f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void CopyFile_internal(const char* file, const char* to)
{
	BBStr* f = toBBStr(file);
	BBStr* t = toBBStr(to);
	bbCopyFile(f, t);
	freeBBStr(f);
	freeBBStr(t);
}

PUBLIC_METHOD void DeleteFile_internal(const char* file)
{
	BBStr* f = toBBStr(file);
	bbDeleteFile(f);
	freeBBStr(f);
}