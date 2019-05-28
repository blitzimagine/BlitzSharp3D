// ==========================================================
// Load From Handle Example
//
// Design and implementation by Floris van den Berg
//
// This file is part of FreeImage
//
// Use at own risk!
// ==========================================================
//
//   This example shows how to load a bitmap from a
//   user allocated FILE pointer.
//
// ==========================================================

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "FreeImage.h"

// ----------------------------------------------------------

unsigned
_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fread(buffer, size, count, (FILE *)handle);
}

unsigned
_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fwrite(buffer, size, count, (FILE *)handle);
}

int
_SeekProc(fi_handle handle, long offset, int origin) {
	return fseek((FILE *)handle, offset, origin);
}

long
_TellProc(fi_handle handle) {
	return ftell((FILE *)handle);
}

// ----------------------------------------------------------

int __cdecl
main(int argc, char *argv[]) {
	FreeImageIO io;

	io.read_proc = _ReadProc;
	io.write_proc = _WriteProc;
	io.seek_proc = _SeekProc;
	io.tell_proc = _TellProc;

	FILE *file = fopen("d:\\images\\money-256.bmp", "rb");

	if (file != NULL) {
		FIBITMAP *dib = FreeImage_LoadBMPFromHandle(&io, (fi_handle)file);

		FreeImage_Free(dib);

		fclose(file);
	}

	return 0;
}