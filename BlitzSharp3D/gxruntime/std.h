
#ifndef STD_H
#define STD_H

#include <fmod.h>

#include "../config/config.h"
#include "../stdutil/stdutil.h"

#pragma warning( disable:4786 )

#ifndef DIRECTSOUND_VERSION
#define DIRECTSOUND_VERSION 0x700
#endif
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x700
#endif

#include <set>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <math.h>
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <d3d.h>

using namespace std;

#endif