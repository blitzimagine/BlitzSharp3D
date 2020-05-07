
#ifndef BBSTREAM_H
#define BBSTREAM_H

#include "bbsys.h"

class bbStream {
public:
	enum {
		EOF_ERROR = -1, EOF_NOT = 0, EOF_OK = 1
	};

	bbStream();
	virtual ~bbStream();

	//returns chars read
	virtual int read(char* buff, int size) = 0;

	//returns chars written
	virtual int write(const char* buff, int size) = 0;

	//returns chars avilable for reading
	virtual int avail() = 0;

	//returns EOF status
	virtual int eof() = 0;
};

void debugStream(bbStream* s);

int bbEof(bbStream* s);
int bbReadAvail(bbStream* s);
int bbReadByte(bbStream* s);
int bbReadShort(bbStream* s);
int bbReadInt(bbStream* s);
float bbReadFloat(bbStream* s);
BBStr* bbReadString(bbStream* s);
BBStr* bbReadLine(bbStream* s);
void bbWriteByte(bbStream* s, int n);
void bbWriteShort(bbStream* s, int n);
void bbWriteInt(bbStream* s, int n);
void bbWriteFloat(bbStream* s, float n);
void bbWriteString(bbStream* s, BBStr* t);
void bbWriteLine(bbStream* s, BBStr* t);
void bbCopyStream(bbStream* s, bbStream* d, int buff_size);

#endif