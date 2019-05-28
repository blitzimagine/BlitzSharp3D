// ==========================================================
// Batch loader
//
// Design and implementation by Floris van den Berg
//
// This file is part of FreeImage
//
// Use at own risk!
// ==========================================================
//
//  This example shows how to easily batch load a directory
//  full of images. Because not all formats can be identified
//  by their header (some images don't have a header or one
//  at the end of the file) we make use of the
//  FreeImage_GetFileTypeFromExt function. This function
//  receives a file extension, for example BMP, and returns
//  a FREE_IMAGE_TYPE enum which identifies that bitmap.
//
// ==========================================================

#include <assert.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>

#include "FreeImage.h"

// ----------------------------------------------------------

int __cdecl
main(int argc, char *argv[]) {
	FIBITMAP *dib = NULL;
	int id = 1;

	printf(FreeImage_GetVersion());
	printf(FreeImage_GetCopyrightMessage());

	// open the log file

	FILE *log_file = fopen("log_file.txt", "w");

	// batch convert all supported bitmaps

	_finddata_t finddata;

	long handle;

	if ((handle = _findfirst("d:\\images\\*.*", &finddata)) != -1) {
		do {
			// grab the extension

			char *ext = new char[4];
			ext[3] = 0;
			strncpy(ext, finddata.name + strlen(finddata.name) - 3, 3);

			// make a path to a directory

			char *directory = new char[128];
			strcpy(directory, "d:\\images\\");
			strcat(directory, finddata.name);

			// make a unique filename

			char *unique = new char[128];
			itoa(id, unique, 10);
			strcat(unique, ".bmp");

			// open the file

			switch(FreeImage_GetFileTypeFromExt(ext)) {
				case FIF_BMP :
					dib = FreeImage_LoadBMP(directory);
					break;

				case FIF_ICO :
					dib = FreeImage_LoadICO(directory);
					break;

				case FIF_JPEG :
					dib = FreeImage_LoadJPEG(directory);
					break;

				case FIF_KOALA :
					dib = FreeImage_LoadKOALA(directory);
					break;

				case FIF_PCD :
					dib = FreeImage_LoadPCD(directory);
					break;

				case FIF_PCX :
					dib = FreeImage_LoadPCX(directory);
					break;

				case FIF_PNG :
					dib = FreeImage_LoadPNG(directory);
					break;

				case FIF_PBM :
					dib = FreeImage_LoadPNM(directory);
					break;

				case FIF_PGM :
					dib = FreeImage_LoadPNM(directory);
					break;

				case FIF_PPM :
					dib = FreeImage_LoadPNM(directory);
					break;

				case FIF_RAS :
					dib = FreeImage_LoadRAS(directory);
					break;

				case FIF_TARGA :
					dib = FreeImage_LoadTARGA(directory);
					break;

				case FIF_TIFF :
					dib = FreeImage_LoadTIFF(directory);
					break;
			};

			if (dib != NULL) {
				FreeImage_SaveBMP(dib, unique);

				FreeImage_Free(dib);

				fwrite(unique, strlen(unique), 1, log_file);
				fwrite(" >> ", 4, 1, log_file);
				fwrite(directory, strlen(directory), 1, log_file);
				fwrite("\n", 1, 1, log_file);

				id++;
			}

			delete [] unique;
			delete [] directory;
			delete [] ext;

		} while (_findnext(handle, &finddata) == 0);

		_findclose(handle);
	}

	fclose(log_file);

	return 0;
}