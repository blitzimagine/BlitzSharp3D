
#ifndef BBFILESYSTEM_H
#define BBFILESYSTEM_H

#include "bbsys.h"
#include "../gxruntime/gxfilesystem.h"

#include "bbstream.h"

extern gxFileSystem* gx_filesys;

struct bbFile : public bbStream {
	filebuf* buf;
	bbFile(filebuf* f) :buf(f) {
	}
	~bbFile() {
		delete buf;
	}
	int read(char* buff, int size) {
		return (int)buf->sgetn((char*)buff, size);
	}
	int write(const char* buff, int size) {
		return (int)buf->sputn((char*)buff, size);
	}
	int avail() {
		return (int)buf->in_avail();
	}
	int eof() {
		return buf->sgetc() == EOF;
	}
};

bbFile* bbReadFile(BBStr* f);
bbFile* bbWriteFile(BBStr* f);
bbFile* bbOpenFile(BBStr* f);
void bbCloseFile(bbFile* f);
int bbFilePos(bbFile* f);
int bbSeekFile(bbFile* f, int pos);
gxDir* bbReadDir(BBStr* d);
void bbCloseDir(gxDir* d);
BBStr* bbNextFile(gxDir* d);
BBStr* bbCurrentDir();
void bbChangeDir(BBStr* d);
void bbCreateDir(BBStr* d);
void bbDeleteDir(BBStr* d);
int bbFileType(BBStr* f);
int	bbFileSize(BBStr* f);
void bbCopyFile(BBStr* f, BBStr* to);
void bbDeleteFile(BBStr* f);

#endif