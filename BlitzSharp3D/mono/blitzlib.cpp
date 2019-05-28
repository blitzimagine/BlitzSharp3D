#include "blitzlib.h"

#include "../bbruntime/bbruntime.h"
#include "../bbruntime/bbgraphics.h"
#include "../bbruntime/bbinput.h"
#include "../bbruntime/bbblitz3d.h"
#include "../bbruntime/bbmath.h"
#include "../bbruntime/bbfilesystem.h"
#include "../bbruntime/multiplay.h"
#include "../bbruntime/bbsockets.h"
#include "../bbruntime/bbaudio.h"
#include "../bbruntime/bbbank.h"

#ifdef _WIN32
#define PUBLIC_METHOD extern "C" __declspec(dllexport)
#else
#define PUBLIC_METHOD extern "C"
#endif

//--------------------------------------------
// Utility
//--------------------------------------------

static inline BBStr* toBBStr(const char* str)
{
	return _bbStrConst(str);
}

static inline void freeBBStr(BBStr* str)
{
	_bbStrRelease(str);
}

static inline const char* toMonoStrNoFree(BBStr* str)
{
    char* ret = static_cast<char*>(malloc(str->length() + 1));
    ret = strcpy(ret, str->c_str());
    ret[str->length()] = 0;
    return ret;
}

static inline const char* toMonoStr(BBStr* str)
{
	const char* ret = toMonoStrNoFree(str);
	freeBBStr(str);
	return ret;
}

//--------------------------------------------
// Public
//--------------------------------------------

PUBLIC_METHOD void RuntimeStats()
{
	bbRuntimeStats();
}

PUBLIC_METHOD int KeyHit(int key)
{
	return bbKeyHit(key) != 0;
}

PUBLIC_METHOD int KeyDown(int key)
{
	return bbKeyDown(key) != 0;
}

PUBLIC_METHOD int GetKey()
{
	return bbGetKey();
}

PUBLIC_METHOD int WaitKey()
{
	return bbWaitKey();
}

PUBLIC_METHOD void FlushKeys()
{
	return bbFlushKeys();
}

PUBLIC_METHOD void Restart()
{
	bbRestart();
}

PUBLIC_METHOD void End()
{
	bbEnd();
}

PUBLIC_METHOD void Stop()
{
	bbStop();
}

PUBLIC_METHOD void AppTitle(const char* title, const char* closePrompt)
{
	BBStr* ti = toBBStr(title);
	BBStr* cp = toBBStr(closePrompt);
	bbAppTitle(ti, cp);
	freeBBStr(ti);
	freeBBStr(cp);
}

PUBLIC_METHOD void RuntimeError(const char* message)
{
	BBStr* msg = toBBStr(message);
	bbRuntimeError(msg);
	freeBBStr(msg);
}

PUBLIC_METHOD int ExecFile(const char* command)
{
	BBStr* cmd = toBBStr(command);
	int ret = bbExecFile(cmd);
	freeBBStr(cmd);
	return ret;
}

PUBLIC_METHOD void Delay(int millisecs)
{
	bbDelay(millisecs);
}

PUBLIC_METHOD int MilliSecs()
{
	return bbMilliSecs();
}

PUBLIC_METHOD void CommandLine_internal(char* ret, int retLen)
{
	BBStr* str = bbCommandLine();
    strcpy_s(ret, retLen, str->c_str());
	freeBBStr(str);
}

PUBLIC_METHOD void SystemProperty_internal(char* ret, int retLen, const char* prop)
{
	BBStr* p = toBBStr(prop);
    strcpy_s(ret, retLen, bbSystemProperty(p)->c_str());
	freeBBStr(p);
}

PUBLIC_METHOD void GetEnv_internal(char* ret, int retLen, const char* env_var)
{
	BBStr* v = toBBStr(env_var);
    strcpy_s(ret, retLen, bbGetEnv(v)->c_str());
	freeBBStr(v);
}

PUBLIC_METHOD void SetEnv(const char* env_var, const char* val)
{
	BBStr* env = toBBStr(env_var);
	BBStr* v = toBBStr(val);
	bbSetEnv(env, v);
	freeBBStr(env);
	freeBBStr(v);
}

PUBLIC_METHOD gxTimer* CreateTimer_internal(int hertz)
{
	return bbCreateTimer(hertz);
}

PUBLIC_METHOD int WaitTimer_internal(gxTimer* timer)
{
	return bbWaitTimer(timer);
}

PUBLIC_METHOD void FreeTimer_internal(gxTimer* timer)
{
	bbFreeTimer(timer);
}

PUBLIC_METHOD void DebugLog(const char* text)
{
	BBStr* txt = toBBStr(text);
	bbDebugLog(txt);
	freeBBStr(txt);
}

// ----
// Math
// ----

PUBLIC_METHOD float Sin(float deg)
{
	return bbSin(deg);
}

PUBLIC_METHOD float Cos(float deg)
{
	return bbCos(deg);
}

PUBLIC_METHOD float Tan(float deg)
{
	return bbTan(deg);
}

PUBLIC_METHOD float ASin(float f)
{
	return bbASin(f);
}

PUBLIC_METHOD float ACos(float f)
{
	return bbACos(f);
}

PUBLIC_METHOD float ATan(float f)
{
	return bbATan(f);
}

PUBLIC_METHOD float ATan2(float n, float t)
{
	return bbATan2(n, t);
}

PUBLIC_METHOD float Sqr(float f)
{
	return bbSqr(f);
}

PUBLIC_METHOD float Floor(float f)
{
	return bbFloor(f);
}

PUBLIC_METHOD float Ceil(float f)
{
	return bbCeil(f);
}

PUBLIC_METHOD float Exp(float f)
{
	return bbExp(f);
}

PUBLIC_METHOD float Log(float f)
{
	return bbLog(f);
}

PUBLIC_METHOD float Log10(float f)
{
	return bbLog10(f);
}

PUBLIC_METHOD float Rnd(float from, float to)
{
	return bbRnd(from, to);
}

PUBLIC_METHOD int Rand(int from, int to)
{
	return bbRand(from, to);
}

PUBLIC_METHOD void SeedRnd(int seed)
{
	return bbSeedRnd(seed);
}

PUBLIC_METHOD int RndSeed()
{
	return bbRndSeed();
}

// ----------
// FileSystem
// ----------

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

// ------
// Stream
// ------

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

// ---------
// Multiplay
// ---------

PUBLIC_METHOD int StartNetGame()
{
	return bbStartNetGame();
}

PUBLIC_METHOD int HostNetGame(const char* gameName)
{
	BBStr* n = toBBStr(gameName);
	int ret = bbHostNetGame(n);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD int JoinNetGame(const char* gameName, const char* ip)
{
	BBStr* n = toBBStr(gameName);
	BBStr* i = toBBStr(ip);
	int ret = bbJoinNetGame(n, i);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void StopNetGame()
{
	bbStopNetGame();
}

PUBLIC_METHOD int CreateNetPlayer(const char* name)
{
	BBStr* n = toBBStr(name);
	int ret = bbCreateNetPlayer(n);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void DeleteNetPlayer(int player)
{
	bbDeleteNetPlayer(player);
}

PUBLIC_METHOD void NetPlayerName_internal(char* ret, int retLen, int player)
{
	BBStr* n = bbNetPlayerName(player);
    strcpy_s(ret, retLen, n->c_str());
	freeBBStr(n);
}

PUBLIC_METHOD int NetPlayerLocal(int player)
{
	return bbNetPlayerLocal(player) != 0;
}

PUBLIC_METHOD int SendNetMsg(int type, const char* msg, int from, int to, int reliable)
{
	BBStr* m = toBBStr(msg);
	int ret = bbSendNetMsg(type, m, from, to, reliable);
	freeBBStr(m);
	return ret;
}

PUBLIC_METHOD int RecvNetMsg()
{
	return bbRecvNetMsg();
}

PUBLIC_METHOD int NetMsgType()
{
	return bbNetMsgType();
}

PUBLIC_METHOD int NetMsgFrom()
{
	return bbNetMsgFrom();
}

PUBLIC_METHOD int NetMsgTo()
{
	return bbNetMsgTo();
}

PUBLIC_METHOD void NetMsgData_internal(char* ret, int retLen)
{
	BBStr* d = bbNetMsgData();
    strcpy_s(ret, retLen, d->c_str());
	freeBBStr(d);
}

// -------
// Sockets
// -------

PUBLIC_METHOD void DottedIP_internal(char* ret, int retLen, int ip)
{
	BBStr* i = bbDottedIP(ip);
    strcpy_s(ret, retLen, i->c_str());
	freeBBStr(i);
}

PUBLIC_METHOD int CountHostIPs(const char* hostName)
{
	BBStr* h = toBBStr(hostName);
	int ret = bbCountHostIPs(h);
	freeBBStr(h);
	return ret;
}

PUBLIC_METHOD int HostIP(int hostIndex)
{
	return bbHostIP(hostIndex);
}

PUBLIC_METHOD UDPStream* CreateUDPStream_internal(int port)
{
	return bbCreateUDPStream(port);
}

PUBLIC_METHOD void CloseUDPStream_internal(UDPStream* stream)
{
	bbCloseUDPStream(stream);
}

PUBLIC_METHOD void SendUDPMsg_internal(UDPStream* stream, int destIp, int destPort)
{
	bbSendUDPMsg(stream, destIp, destPort);
}

PUBLIC_METHOD int RecvUDPMsg_internal(UDPStream* stream)
{
	return bbRecvUDPMsg(stream);
}

PUBLIC_METHOD int UDPStreamIP_internal(UDPStream* stream)
{
	return bbUDPStreamIP(stream);
}

PUBLIC_METHOD int UDPStreamPort_internal(UDPStream* stream)
{
	return bbUDPStreamPort(stream);
}

PUBLIC_METHOD int UDPMsgIP_internal(UDPStream* stream)
{
	return bbUDPMsgIP(stream);
}

PUBLIC_METHOD int UDPMsgPort_internal(UDPStream* stream)
{
	return bbUDPMsgPort(stream);
}

PUBLIC_METHOD void UDPTimeouts(int recvTimeout)
{
	return bbUDPTimeouts(recvTimeout);
}

PUBLIC_METHOD TCPStream* OpenTCPStream_internal(const char* server, int serverPort, int localPort)
{
	BBStr* s = toBBStr(server);
	TCPStream* ret = bbOpenTCPStream(s, serverPort, localPort);
	freeBBStr(s);
	return ret;
}

PUBLIC_METHOD void CloseTCPStream_internal(TCPStream* stream)
{
	bbCloseTCPStream(stream);
}

PUBLIC_METHOD TCPServer* CreateTCPServer_internal(int port)
{
	return bbCreateTCPServer(port);
}

PUBLIC_METHOD void CloseTCPServer_internal(TCPServer* server)
{
	bbCloseTCPServer(server);
}

PUBLIC_METHOD TCPStream* AcceptTCPStream_internal(TCPServer* server)
{
	return bbAcceptTCPStream(server);
}

PUBLIC_METHOD int TCPStreamIP_internal(TCPStream* stream)
{
	return bbTCPStreamIP(stream);
}

PUBLIC_METHOD int TCPStreamPort_internal(TCPStream* stream)
{
	return bbTCPStreamPort(stream);
}

PUBLIC_METHOD void TCPTimeouts(int readTime, int acceptTime)
{
	bbTCPTimeouts(readTime, acceptTime);
}

// -----
// Input
// -----

PUBLIC_METHOD int MouseDown(int button)
{
	return bbMouseDown(button) != 0;
}

PUBLIC_METHOD int MouseHit(int button)
{
	return bbMouseHit(button) != 0;
}

PUBLIC_METHOD int GetMouse()
{
	return bbGetMouse();
}

PUBLIC_METHOD int WaitMouse()
{
	return bbWaitMouse();
}

// Matt: Why exactly is there an extra copy of this?
PUBLIC_METHOD int MouseWait()
{
	return bbWaitMouse();
}

PUBLIC_METHOD int MouseX()
{
	return bbMouseX();
}

PUBLIC_METHOD int MouseY()
{
	return bbMouseY();
}

PUBLIC_METHOD int MouseZ()
{
	return bbMouseZ();
}

PUBLIC_METHOD int MouseXSpeed()
{
	return bbMouseXSpeed();
}

PUBLIC_METHOD int MouseYSpeed()
{
	return bbMouseYSpeed();
}

PUBLIC_METHOD int MouseZSpeed()
{
	return bbMouseZSpeed();
}

PUBLIC_METHOD void FlushMouse()
{
	bbFlushMouse();
}

PUBLIC_METHOD void MoveMouse(int x, int y)
{
	bbMoveMouse(x, y);
}

PUBLIC_METHOD int JoyType(int port)
{
	return bbJoyType(port);
}

PUBLIC_METHOD int JoyDown(int button, int port)
{
	return bbJoyDown(button, port) != 0;
}

PUBLIC_METHOD int JoyHit(int button, int port)
{
	return bbJoyHit(button, port) != 0;
}

PUBLIC_METHOD int GetJoy(int port)
{
	return bbGetJoy(port);
}

PUBLIC_METHOD int WaitJoy(int port)
{
	return bbWaitJoy(port);
}

// Matt: Again, why is there an extra copy of this?
PUBLIC_METHOD int JoyWait(int port)
{
	return bbWaitJoy(port);
}

PUBLIC_METHOD float JoyX(int port)
{
	return bbJoyX(port);
}

PUBLIC_METHOD float JoyY(int port)
{
	return bbJoyY(port);
}

PUBLIC_METHOD float JoyZ(int port)
{
	return bbJoyZ(port);
}

PUBLIC_METHOD float JoyU(int port)
{
	return bbJoyU(port);
}

PUBLIC_METHOD float JoyV(int port)
{
	return bbJoyV(port);
}

PUBLIC_METHOD float JoyPitch(int port)
{
	return bbJoyPitch(port);
}

PUBLIC_METHOD float JoyYaw(int port)
{
	return bbJoyYaw(port);
}

PUBLIC_METHOD float JoyRoll(int port)
{
	return bbJoyRoll(port);
}

PUBLIC_METHOD int JoyHat(int port)
{
	return bbJoyHat(port);
}

PUBLIC_METHOD int JoyXDir(int port)
{
	return bbJoyXDir(port);
}

PUBLIC_METHOD int JoyYDir(int port)
{
	return bbJoyYDir(port);
}

PUBLIC_METHOD int JoyZDir(int port)
{
	return bbJoyZDir(port);
}

PUBLIC_METHOD int JoyUDir(int port)
{
	return bbJoyUDir(port);
}

PUBLIC_METHOD int JoyVDir(int port)
{
	return bbJoyVDir(port);
}

PUBLIC_METHOD int JoyPitchDir(int port)
{
  return bbJoyPitchDir(port);
}

PUBLIC_METHOD int JoyYawDir(int port)
{
  return bbJoyYawDir(port);
}

PUBLIC_METHOD int JoyRollDir(int port)
{
  return bbJoyRollDir(port);
}

PUBLIC_METHOD void FlushJoy()
{
	bbFlushJoy();
}

PUBLIC_METHOD void EnableDirectInput(int enable)
{
	bbEnableDirectInput(enable ? 1 : 0);
}

PUBLIC_METHOD int DirectInputEnabled()
{
	return bbDirectInputEnabled() != 0;
}

// -----
// Audio
// -----

PUBLIC_METHOD gxSound* LoadSound_internal(const char* filename)
{
	BBStr* f = toBBStr(filename);
	gxSound* ret = bbLoadSound(f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void FreeSound_internal(gxSound* sound)
{
	bbFreeSound(sound);
}

PUBLIC_METHOD void LoopSound_internal(gxSound* sound)
{
	bbLoopSound(sound);
}

PUBLIC_METHOD void SoundPitch_internal(gxSound* sound, int pitch)
{
	bbSoundPitch(sound, pitch);
}

PUBLIC_METHOD void SoundVolume_internal(gxSound* sound, float volume)
{
	bbSoundVolume(sound, volume);
}

PUBLIC_METHOD void SoundPan_internal(gxSound* sound, float pan)
{
	bbSoundPan(sound, pan);
}

PUBLIC_METHOD gxChannel* PlaySound_internal(gxSound* sound)
{
	return bbPlaySound(sound);
}

PUBLIC_METHOD gxChannel* PlayMusic_internal(const char* midifile)
{
	BBStr* f = toBBStr(midifile);
	gxChannel* ret = bbPlayMusic(f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD gxChannel* PlayCDTrack_internal(int track, int mode)
{
	return bbPlayCDTrack(track, mode);
}

PUBLIC_METHOD void StopChannel_internal(gxChannel* channel)
{
	bbStopChannel(channel);
}

PUBLIC_METHOD void PauseChannel_internal(gxChannel* channel)
{
	bbPauseChannel(channel);
}

PUBLIC_METHOD void ResumeChannel_internal(gxChannel* channel)
{
	bbResumeChannel(channel);
}

PUBLIC_METHOD void ChannelPitch_internal(gxChannel* channel, int pitch)
{
	bbChannelPitch(channel, pitch);
}

PUBLIC_METHOD void ChannelVolume_internal(gxChannel* channel, float volume)
{
	bbChannelVolume(channel, volume);
}

PUBLIC_METHOD void ChannelPan_internal(gxChannel* channel, float pan)
{
	bbChannelPan(channel, pan);
}

PUBLIC_METHOD int ChannelPlaying_internal(gxChannel* channel)
{
	return bbChannelPlaying(channel) != 0;
}

PUBLIC_METHOD gxSound* Load3DSound_internal(const char* filename)
{
	BBStr* f = toBBStr(filename);
	gxSound* ret = bbLoad3DSound(f);
	freeBBStr(f);
	return ret;
}

// ----
// Bank
// ----

PUBLIC_METHOD bbBank* CreateBank_internal(int size)
{
	return bbCreateBank(size);
}

PUBLIC_METHOD void FreeBank_internal(bbBank* bank)
{
	bbFreeBank(bank);
}

PUBLIC_METHOD int BankSize_internal(bbBank* bank)
{
	return bbBankSize(bank);
}

PUBLIC_METHOD void ResizeBank_internal(bbBank* bank, int size)
{
	bbResizeBank(bank, size);
}

PUBLIC_METHOD void CopyBank_internal(bbBank* src, int srcOffset, bbBank* dest, int destOffset, int count)
{
	bbCopyBank(src, srcOffset, dest, destOffset, count);
}

PUBLIC_METHOD char PeekByte_internal(bbBank* bank, int offset)
{
	return (char)bbPeekByte(bank, offset);
}

PUBLIC_METHOD short PeekShort_internal(bbBank* bank, int offset)
{
	return (short)bbPeekShort(bank, offset);
}

PUBLIC_METHOD int PeekInt_internal(bbBank* bank, int offset)
{
	return bbPeekInt(bank, offset);
}

PUBLIC_METHOD float PeekFloat_internal(bbBank* bank, int offset)
{
	return bbPeekFloat(bank, offset);
}

PUBLIC_METHOD void PokeByte_internal(bbBank* bank, int offset, char value)
{
	bbPokeByte(bank, offset, value);
}

PUBLIC_METHOD void PokeShort_internal(bbBank* bank, int offset, short value)
{
	bbPokeShort(bank, offset, value);
}

PUBLIC_METHOD void PokeInt_internal(bbBank* bank, int offset, int value)
{
	bbPokeInt(bank, offset, value);
}

PUBLIC_METHOD void PokeFloat_internal(bbBank* bank, int offset, float value)
{
	bbPokeFloat(bank, offset, value);
}

PUBLIC_METHOD int ReadBytes_internal(bbBank* bank, bbStream* stream, int offset, int count)
{
	return bbReadBytes(bank, stream, offset, count);
}

PUBLIC_METHOD int WriteBytes_internal(bbBank* bank, bbStream* stream, int offset, int count)
{
	return bbWriteBytes(bank, stream, offset, count);
}

PUBLIC_METHOD int CallDLL_internal(const char* dll, const char* func, bbBank* in, bbBank* out)
{
	BBStr* d = toBBStr(dll);
	BBStr* f = toBBStr(func);
	int ret = bbCallDLL(d, f, in, out);
	freeBBStr(f);
	freeBBStr(d);
	return ret;
}

// --------
// Graphics
// --------

PUBLIC_METHOD int CountGfxDrivers()
{
	return bbCountGfxDrivers();
}

PUBLIC_METHOD void GfxDriverName_internal(char* ret, int retLen, int driver)
{
	strcpy_s(ret, retLen, toMonoStr(bbGfxDriverName(driver)));
}

PUBLIC_METHOD void SetGfxDriver(int driver)
{
	bbSetGfxDriver(driver);
}

PUBLIC_METHOD int CountGfxModes()
{
	return bbCountGfxModes();
}

PUBLIC_METHOD int GfxModeExists(int width, int height, int depth)
{
	return bbGfxModeExists(width, height, depth) != 0;
}

PUBLIC_METHOD int GfxModeWidth(int mode)
{
	return bbGfxModeWidth(mode);
}

PUBLIC_METHOD int GfxModeHeight(int mode)
{
	return bbGfxModeHeight(mode);
}

PUBLIC_METHOD int GfxModeDepth(int mode)
{
	return bbGfxModeDepth(mode);
}

PUBLIC_METHOD int AvailVidMem()
{
	return bbAvailVidMem();
}

PUBLIC_METHOD int TotalVidMem()
{
	return bbTotalVidMem();
}

PUBLIC_METHOD int GfxDriver3D(int driver)
{
	return bbGfxDriver3D(driver) != 0;
}

PUBLIC_METHOD int CountGfxModes3D()
{
	return bbCountGfxModes3D();
}

PUBLIC_METHOD int GfxMode3DExists(int width, int height, int depth)
{
	return bbGfxMode3DExists(width, height, depth) != 0;
}

PUBLIC_METHOD int GfxMode3D(int mode)
{
	return bbGfxMode3D(mode) != 0;
}

PUBLIC_METHOD int Windowed3D()
{
	return bbWindowed3D() != 0;
}

PUBLIC_METHOD void Graphics(int width, int height, int depth, int mode, int monitor)
{
	bbGraphics(width, height, depth, mode, monitor);
}

PUBLIC_METHOD void Graphics3D(int width, int height, int depth, int mode, int monitor)
{
	bbGraphics3D(width, height, depth, mode, monitor);
}

PUBLIC_METHOD void EndGraphics()
{
	bbEndGraphics();
}

PUBLIC_METHOD int SetGraphicsMode_internal(int width, int height, int depth, int mode, int monitor)
{
	return bbSetGraphicsMode(width, height, depth, mode, monitor);
}

PUBLIC_METHOD int GraphicsLost()
{
	return bbGraphicsLost() != 0;
}

PUBLIC_METHOD int IsFocused()
{
  return bbIsFocused() != 0;
}

PUBLIC_METHOD void SetGamma(int srcRed, int srcGreen, int srcBlue, float destRed, float destGreen, float destBlue)
{
	bbSetGamma(srcRed, srcGreen, srcBlue, destRed, destGreen, destBlue);
}

PUBLIC_METHOD void UpdateGamma(int calibrate)
{
	bbUpdateGamma(calibrate ? 1 : 0);
}

PUBLIC_METHOD float GammaRed(int red)
{
	return bbGammaRed(red);
}

PUBLIC_METHOD float GammaGreen(int red)
{
	return bbGammaGreen(red);
}

PUBLIC_METHOD float GammaBlue(int red)
{
	return bbGammaBlue(red);
}

PUBLIC_METHOD gxCanvas* FrontBuffer_internal()
{
	return bbFrontBuffer();
}

PUBLIC_METHOD gxCanvas* BackBuffer_internal()
{
	return bbBackBuffer();
}

PUBLIC_METHOD int ScanLine()
{
	return bbScanLine();
}

PUBLIC_METHOD void VWait(int frames)
{
	bbVWait(frames);
}

PUBLIC_METHOD void Flip(int vwait)
{
	bbFlip(vwait ? 1 : 0);
}

PUBLIC_METHOD int GraphicsWidth()
{
	return bbGraphicsWidth();
}

PUBLIC_METHOD int GraphicsHeight()
{
	return bbGraphicsHeight();
}

PUBLIC_METHOD int GraphicsDepth()
{
	return bbGraphicsDepth();
}

PUBLIC_METHOD void SetBuffer_internal(gxCanvas* buffer)
{
	bbSetBuffer(buffer);
}

PUBLIC_METHOD gxCanvas* GraphicsBuffer_internal()
{
	return bbGraphicsBuffer();
}

PUBLIC_METHOD int LoadBuffer_internal(gxCanvas* buffer, const char* bmpFile)
{
	BBStr* bmp = toBBStr(bmpFile);
	int ret = bbLoadBuffer(buffer, bmp);
	freeBBStr(bmp);
	return ret != 0;
}

PUBLIC_METHOD int SaveBuffer_internal(gxCanvas* buffer, const char* bmpFile)
{
	BBStr* bmp = toBBStr(bmpFile);
	int ret = bbSaveBuffer(buffer, bmp);
	freeBBStr(bmp);
	return ret != 0;
}

PUBLIC_METHOD void BufferDirty_internal(gxCanvas* buffer)
{
	bbBufferDirty(buffer);
}

PUBLIC_METHOD void LockBuffer_internal(gxCanvas* buffer)
{
	bbLockBuffer(buffer);
}

PUBLIC_METHOD void UnlockBuffer_internal(gxCanvas* buffer)
{
	bbUnlockBuffer(buffer);
}

PUBLIC_METHOD int ReadPixel_internal(int x, int y, gxCanvas* buffer)
{
	return bbReadPixel(x, y, buffer);
}

PUBLIC_METHOD void WritePixel_internal(int x, int y, int argb, gxCanvas* buffer)
{
	bbWritePixel(x, y, argb, buffer);
}

PUBLIC_METHOD int ReadPixelFast_internal(int x, int y, gxCanvas* buffer)
{
	return bbReadPixelFast(x, y, buffer);
}

PUBLIC_METHOD void WritePixelFast_internal(int x, int y, int argb, gxCanvas* buffer)
{
	bbWritePixelFast(x, y, argb, buffer);
}

PUBLIC_METHOD void CopyPixel_internal(int srcX, int srcY, gxCanvas* srcBuffer, int destX, int destY, gxCanvas* destBuffer)
{
	bbCopyPixel(srcX, srcY, srcBuffer, destX, destY, destBuffer);
}

PUBLIC_METHOD void CopyPixelFast_internal(int srcX, int srcY, gxCanvas* srcBuffer, int destX, int destY, gxCanvas* destBuffer)
{
	bbCopyPixelFast(srcX, srcY, srcBuffer, destX, destY, destBuffer);
}

PUBLIC_METHOD void Origin(int x, int y)
{
	bbOrigin(x, y);
}

PUBLIC_METHOD void Viewport(int x, int y, int width, int height)
{
	bbViewport(x, y, width, height);
}

PUBLIC_METHOD void Color(int r, int g, int b)
{
	bbColor(r, g, b);
}

PUBLIC_METHOD void GetColor(int x, int y)
{
	bbGetColor(x, y);
}

PUBLIC_METHOD int ColorRed()
{
	return bbColorRed();
}

PUBLIC_METHOD int ColorGreen()
{
	return bbColorGreen();
}

PUBLIC_METHOD int ColorBlue()
{
	return bbColorBlue();
}

PUBLIC_METHOD void ClsColor(int r, int g, int b)
{
	bbClsColor(r, g, b);
}

PUBLIC_METHOD void SetFont_internal(gxFont* font)
{
	bbSetFont(font);
}

PUBLIC_METHOD void Cls()
{
	bbCls();
}

PUBLIC_METHOD void Plot(int x, int y)
{
	bbPlot(x, y);
}

PUBLIC_METHOD void Rect(int x, int y, int width, int height, int solid)
{
	bbRect(x, y, width, height, solid ? 1 : 0);
}

PUBLIC_METHOD void Oval(int x, int y, int width, int height, int solid)
{
	bbOval(x, y, width, height, solid ? 1 : 0);
}

PUBLIC_METHOD void Line(int x1, int y1, int x2, int y2)
{
	bbLine(x1, y1, x2, y2);
}

PUBLIC_METHOD void Text(int x, int y, const char* str, int centerX, int centerY)
{
	BBStr* s = toBBStr(str);
	bbText(x, y, s, centerX, centerY);
	freeBBStr(s);
}

PUBLIC_METHOD void CopyRect_internal(int srcX, int srcY, int width, int height, int destX, int destY, gxCanvas* srcBuffer, gxCanvas* destBuffer)
{
	bbCopyRect(srcX, srcY, width, height, destX, destY, srcBuffer, destBuffer);
}

PUBLIC_METHOD gxFont* LoadFont_internal(const char* name, int height, int bold, int italic, int underline)
{
	BBStr* n = toBBStr(name);
	gxFont* ret = bbLoadFont(n, height, bold != 0, italic != 0, underline != 0);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void FreeFont_internal(gxFont* font)
{
	bbFreeFont(font);
}

PUBLIC_METHOD int FontWidth()
{
	return bbFontWidth();
}

PUBLIC_METHOD int FontHeight()
{
	return bbFontHeight();
}

PUBLIC_METHOD int StringWidth(const char* str)
{
	BBStr* s = toBBStr(str);
	int ret = bbStringWidth(s);
	freeBBStr(s);
	return ret;
}

PUBLIC_METHOD int StringHeight(const char* str)
{
	BBStr* s = toBBStr(str);
	int ret = bbStringHeight(s);
	freeBBStr(s);
	return ret;
}

PUBLIC_METHOD gxMovie* OpenMovie_internal(const char* file)
{
	BBStr* f = toBBStr(file);
	gxMovie* ret = bbOpenMovie(f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD int DrawMovie_internal(gxMovie* movie, int x, int y, int width, int height)
{
	return bbDrawMovie(movie, x, y, width, height) != 0;
}

PUBLIC_METHOD int MovieWidth_internal(gxMovie* movie)
{
	return bbMovieWidth(movie);
}

PUBLIC_METHOD int MovieHeight_internal(gxMovie* movie)
{
	return bbMovieHeight(movie);
}

PUBLIC_METHOD int MoviePlaying_internal(gxMovie* movie)
{
	return bbMoviePlaying(movie) != 0;
}

PUBLIC_METHOD void CloseMovie_internal(gxMovie* movie)
{
	bbCloseMovie(movie);
}

PUBLIC_METHOD bbImage* LoadImage_internal(const char* bmpFile)
{
	BBStr* bmp = toBBStr(bmpFile);
	bbImage* ret = bbLoadImage(bmp);
	freeBBStr(bmp);
	return ret;
}

PUBLIC_METHOD bbImage* LoadAnimImage_internal(const char* bmpFile, int cellwidth, int cellheight, int first, int count)
{
	BBStr* bmp = toBBStr(bmpFile);
	bbImage* ret = bbLoadAnimImage(bmp, cellwidth, cellheight, first, count);
	freeBBStr(bmp);
	return ret;
}

PUBLIC_METHOD bbImage* CopyImage_internal(bbImage* image)
{
	return bbCopyImage(image);
}

PUBLIC_METHOD bbImage* CreateImage_internal(int width, int height, int frames)
{
	return bbCreateImage(width, height, frames);
}

PUBLIC_METHOD void FreeImage_internal(bbImage* image)
{
	bbFreeImage(image);
}

PUBLIC_METHOD int SaveImage_internal(bbImage* image, const char* bmpFile, int frame)
{
	BBStr* bmp = toBBStr(bmpFile);
	int ret = bbSaveImage(image, bmp, frame);
	freeBBStr(bmp);
	return ret != 0;
}

PUBLIC_METHOD void GrabImage_internal(bbImage* image, int x, int y, int frame)
{
	bbGrabImage(image, x, y, frame);
}

PUBLIC_METHOD gxCanvas* ImageBuffer_internal(bbImage* image, int frame)
{
	return bbImageBuffer(image, frame);
}

PUBLIC_METHOD void DrawImage_internal(bbImage* image, int x, int y, int frame)
{
	bbDrawImage(image, x, y, frame);
}

PUBLIC_METHOD void DrawBlock_internal(bbImage* image, int x, int y, int frame)
{
	bbDrawBlock(image, x, y, frame);
}

PUBLIC_METHOD void TileImage_internal(bbImage* image, int x, int y, int frame)
{
	bbTileImage(image, x, y, frame);
}

PUBLIC_METHOD void TileBlock_internal(bbImage* image, int x, int y, int frame)
{
	bbTileBlock(image, x, y, frame);
}

PUBLIC_METHOD void DrawImageRect_internal(bbImage* image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame)
{
	bbDrawImageRect(image, x, y, rectX, rectY, rectWidth, rectHeight, frame);
}

PUBLIC_METHOD void DrawBlockRect_internal(bbImage* image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int frame)
{
	bbDrawBlockRect(image, x, y, rectX, rectY, rectWidth, rectHeight, frame);
}

PUBLIC_METHOD void MaskImage_internal(bbImage* image, int red, int green, int blue)
{
	bbMaskImage(image, red, green, blue);
}

PUBLIC_METHOD void HandleImage_internal(bbImage* image, int x, int y)
{
	bbHandleImage(image, x, y);
}

PUBLIC_METHOD void MidHandle_internal(bbImage* image)
{
	bbMidHandle(image);
}

PUBLIC_METHOD void AutoMidHandle(int enable)
{
	bbAutoMidHandle(enable ? 1 : 0);
}

PUBLIC_METHOD int ImageWidth_internal(bbImage* image)
{
	return bbImageWidth(image);
}

PUBLIC_METHOD int ImageHeight_internal(bbImage* image)
{
	return bbImageHeight(image);
}

PUBLIC_METHOD int ImageXHandle_internal(bbImage* image)
{
	return bbImageXHandle(image);
}

PUBLIC_METHOD int ImageYHandle_internal(bbImage* image)
{
	return bbImageYHandle(image);
}

PUBLIC_METHOD void ScaleImage_internal(bbImage* image, float xscale, float yscale)
{
	bbScaleImage(image, xscale, yscale);
}

PUBLIC_METHOD void ResizeImage_internal(bbImage* image, float width, float height)
{
	bbResizeImage(image, width, height);
}

PUBLIC_METHOD void RotateImage_internal(bbImage* image, float angle)
{
	bbRotateImage(image, angle);
}

PUBLIC_METHOD void TFormImage_internal(bbImage* image, float a, float b, float c, float d)
{
	bbTFormImage(image, a, b, c, d);
}

PUBLIC_METHOD void TFormFilter(int enable)
{
	bbTFormFilter(enable ? 1 : 0);
}

PUBLIC_METHOD int ImagesOverlap_internal(bbImage* image1, int x1, int y1, bbImage* image2, int x2, int y2)
{
	return bbImagesOverlap(image1, x1, y1, image2, x2, y2) != 0;
}

PUBLIC_METHOD int ImagesCollide_internal(bbImage* image1, int x1, int y1, int frame1, bbImage* image2, int x2, int y2, int frame2)
{
	return bbImagesCollide(image1, x1, y1, frame1, image2, x2, y2, frame2) != 0;
}

PUBLIC_METHOD int RectsOverlap(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	return bbRectsOverlap(x1, y1, width1, height1, x2, y2, width2, height2) != 0;
}

PUBLIC_METHOD int ImageRectOverlap_internal(bbImage* image, int x, int y, int rectX, int rectY, int rectWidth, int rectHeight)
{
	return bbImageRectOverlap(image, x, y, rectX, rectY, rectWidth, rectHeight) != 0;
}

PUBLIC_METHOD int ImageRectCollide_internal(bbImage* image, int x, int y, int frame, int rectX, int rectY, int rectWidth, int rectHeight)
{
	return bbImageRectCollide(image, x, y, frame, rectX, rectY, rectWidth, rectHeight) != 0;
}

PUBLIC_METHOD void Write(const char* str)
{
	BBStr* s = toBBStr(str);
	bbWrite(s);
	freeBBStr(s);
}

PUBLIC_METHOD void Print(const char* str)
{
	BBStr* s = toBBStr(str);
	bbPrint(s);
	freeBBStr(s);
}

PUBLIC_METHOD void Input_internal(char* ret, int retLen, const char* prompt)
{
	BBStr* p = toBBStr(prompt);
	BBStr* r = bbInput(p);
    strcpy_s(ret, retLen, toMonoStr(r));
	freeBBStr(p);
}

PUBLIC_METHOD void Locate(int x, int y)
{
	bbLocate(x, y);
}

PUBLIC_METHOD void ShowPointer()
{
	bbShowPointer();
}

PUBLIC_METHOD void HidePointer()
{
	bbHidePointer();
}

// -------
// Blitz3D
// -------

PUBLIC_METHOD void LoaderMatrix(const char* fileExt, float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz)
{
	BBStr* ext = toBBStr(fileExt);
	bbLoaderMatrix(ext, xx, xy, xz, yx, yy, yz, zx, zy, zz);
	freeBBStr(ext);
}

PUBLIC_METHOD void HWMultiTex(int enable)
{
	bbHWMultiTex(enable ? 1 : 0);
}

PUBLIC_METHOD int HWTexUnits()
{
	return bbHWTexUnits();
}

PUBLIC_METHOD int GfxDriverCaps3D()
{
	return bbGfxDriverCaps3D();
}

PUBLIC_METHOD void WBuffer(int enable)
{
	bbWBuffer(enable ? 1 : 0);
}

PUBLIC_METHOD void Dither(int enable)
{
	bbDither(enable ? 1 : 0);
}

PUBLIC_METHOD void AntiAlias(int enable)
{
	bbAntiAlias(enable ? 1 : 0);
}

PUBLIC_METHOD void WireFrame(int enable)
{
	bbWireFrame(enable ? 1 : 0);
}

PUBLIC_METHOD void AmbientLight(float red, float green, float blue)
{
	bbAmbientLight(red, green, blue);
}

PUBLIC_METHOD void ClearCollisions()
{
	bbClearCollisions();
}

PUBLIC_METHOD void Collisions(int srcType, int destType, int method, int response)
{
	bbCollisions(srcType, destType, method, response);
}

PUBLIC_METHOD void UpdateWorld(float elapsed)
{
	bbUpdateWorld(elapsed);
}

PUBLIC_METHOD void CaptureWorld()
{
	bbCaptureWorld();
}

PUBLIC_METHOD void RenderWorld(float tween)
{
	bbRenderWorld(tween);
}

PUBLIC_METHOD void ClearWorld(int entities, int brushes, int textures)
{
	bbClearWorld(entities ? 1 : 0, brushes ? 1 : 0, textures ? 1 : 0);
}

PUBLIC_METHOD int ActiveTextures()
{
	return bbActiveTextures();
}

PUBLIC_METHOD int TrisRendered()
{
	return bbTrisRendered();
}

PUBLIC_METHOD float Stats3D(int type)
{
	return bbStats3D(type);
}

PUBLIC_METHOD Texture* CreateTexture_internal(int width, int height, int flags, int frames)
{
	return bbCreateTexture(width, height, flags, frames);
}

PUBLIC_METHOD Texture* LoadTexture_internal(const char* file, int flags)
{
	BBStr* f = toBBStr(file);
	Texture* ret = bbLoadTexture(f, flags);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD Texture* LoadAnimTexture_internal(const char* file, int flags, int width, int height, int first, int count)
{
	BBStr* f = toBBStr(file);
	Texture* ret = bbLoadAnimTexture(f, flags, width, height, first, count);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void FreeTexture_internal(Texture* texture)
{
	bbFreeTexture(texture);
}

PUBLIC_METHOD void TextureBlend_internal(Texture* texture, int blend)
{
	bbTextureBlend(texture, blend);
}

PUBLIC_METHOD void TextureCoords_internal(Texture* texture, int coords)
{
	bbTextureCoords(texture, coords);
}

PUBLIC_METHOD void ScaleTexture_internal(Texture* texture, float uScale, float vScale)
{
	bbScaleTexture(texture, uScale, vScale);
}

PUBLIC_METHOD void RotateTexture_internal(Texture* texture, float angle)
{
	bbRotateTexture(texture, angle);
}

PUBLIC_METHOD void PositionTexture_internal(Texture* texture, float uOffset, float vOffset)
{
	bbPositionTexture(texture, uOffset, vOffset);
}

PUBLIC_METHOD int TextureWidth_internal(Texture* texture)
{
	return bbTextureWidth(texture);
}

PUBLIC_METHOD int TextureHeight_internal(Texture* texture)
{
	return bbTextureHeight(texture);
}

PUBLIC_METHOD void TextureName_internal(char* ret, int retLen, Texture* texture)
{
	strcpy_s(ret, retLen, toMonoStr(bbTextureName(texture)));
}

PUBLIC_METHOD void SetCubeFace_internal(Texture* texture, int face)
{
	bbSetCubeFace(texture, face);
}

PUBLIC_METHOD void SetCubeMode_internal(Texture* texture, int mode)
{
	bbSetCubeMode(texture, mode);
}

PUBLIC_METHOD gxCanvas* TextureBuffer_internal(Texture* texture, int frame)
{
	return bbTextureBuffer(texture, frame);
}

PUBLIC_METHOD void ClearTextureFilters()
{
	bbClearTextureFilters();
}

PUBLIC_METHOD void TextureFilter(const char* matchText, int textureFlags)
{
	BBStr* m = toBBStr(matchText);
	bbTextureFilter(m, textureFlags);
	freeBBStr(m);
}

PUBLIC_METHOD Brush* CreateBrush_internal(float red, float green, float blue)
{
	return bbCreateBrush(red, green, blue);
}

PUBLIC_METHOD Brush* LoadBrush_internal(const char* file, int textureFlags, float uScale, float vScale)
{
	BBStr* f = toBBStr(file);
	Brush* ret = bbLoadBrush(f, textureFlags, uScale, vScale);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void FreeBrush_internal(Brush* brush)
{
	bbFreeBrush(brush);
}

PUBLIC_METHOD void BrushColor_internal(Brush* brush, float red, float green, float blue)
{
	bbBrushColor(brush, red, green, blue);
}

PUBLIC_METHOD void BrushAlpha_internal(Brush* brush, float alpha)
{
	bbBrushAlpha(brush, alpha);
}

PUBLIC_METHOD void BrushShininess_internal(Brush* brush, float shininess)
{
	bbBrushShininess(brush, shininess);
}

PUBLIC_METHOD void BrushTexture_internal(Brush* brush, Texture* texture, int frame, int index)
{
	bbBrushTexture(brush, texture, frame, index);
}

PUBLIC_METHOD Texture* GetBrushTexture_internal(Brush* brush, int index)
{
	return bbGetBrushTexture(brush, index);
}

PUBLIC_METHOD void BrushBlend_internal(Brush* brush, int blend)
{
	bbBrushBlend(brush, blend);
}

PUBLIC_METHOD void BrushFX_internal(Brush* brush, int fx)
{
	bbBrushFX(brush, fx);
}

PUBLIC_METHOD Entity* LoadMesh_internal(const char* file, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadMesh(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD Entity* LoadAnimMesh_internal(const char* file, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadAnimMesh(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD int LoadAnimSeq_internal(Entity* entity, const char* file)
{
	BBStr* f = toBBStr(file);
	int ret = bbLoadAnimSeq((Object*)entity, f);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD Entity* CreateMesh_internal(Entity* parent)
{
	return bbCreateMesh(parent);
}

PUBLIC_METHOD Entity* CreateCube_internal(Entity* parent)
{
	return bbCreateCube(parent);
}

PUBLIC_METHOD Entity* CreateSphere_internal(int segments, Entity* parent)
{
	return bbCreateSphere(segments, parent);
}

PUBLIC_METHOD Entity* CreateCylinder_internal(int segments, int solid, Entity* parent)
{
	return bbCreateCylinder(segments, solid ? 1 : 0, parent);
}

PUBLIC_METHOD Entity* CreateCone_internal(int segments, int solid, Entity* parent)
{
	return bbCreateCone(segments, solid ? 1 : 0, parent);
}

PUBLIC_METHOD Entity* CopyMesh_internal(Entity* mesh, Entity* parent)
{
	return bbCopyMesh((MeshModel*)mesh, parent);
}

PUBLIC_METHOD void ScaleMesh_internal(Entity* mesh, float xScale, float yScale, float zScale)
{
	bbScaleMesh((MeshModel*)mesh, xScale, yScale, zScale);
}

PUBLIC_METHOD void RotateMesh_internal(Entity* mesh, float pitch, float yaw, float roll)
{
	bbRotateMesh((MeshModel*)mesh, pitch, yaw, roll);
}

PUBLIC_METHOD void PositionMesh_internal(Entity* mesh, float x, float y, float z)
{
	bbPositionMesh((MeshModel*)mesh, x, y, z);
}

PUBLIC_METHOD void FitMesh_internal(Entity* mesh, float x, float y, float z, float width, float height, float depth, int uniform)
{
	bbFitMesh((MeshModel*)mesh, x, y, z, width, height, depth, uniform ? 1 : 0);
}

PUBLIC_METHOD void FlipMesh_internal(Entity* mesh)
{
	bbFlipMesh((MeshModel*)mesh);
}

PUBLIC_METHOD void PaintMesh_internal(Entity* mesh, Brush* brush)
{
	bbPaintMesh((MeshModel*)mesh, brush);
}

PUBLIC_METHOD void AddMesh_internal(Entity* srcMesh, Entity* destMesh)
{
	bbAddMesh((MeshModel*)srcMesh, (MeshModel*)destMesh);
}

PUBLIC_METHOD void UpdateNormals_internal(Entity* mesh)
{
	bbUpdateNormals((MeshModel*)mesh);
}

PUBLIC_METHOD void LightMesh_internal(Entity* mesh, float red, float green, float blue, float range, float x, float y, float z)
{
	bbLightMesh((MeshModel*)mesh, red, green, blue, range, x, y, z);
}

PUBLIC_METHOD float MeshWidth_internal(Entity* mesh)
{
	return bbMeshWidth((MeshModel*)mesh);
}

PUBLIC_METHOD float MeshHeight_internal(Entity* mesh)
{
	return bbMeshHeight((MeshModel*)mesh);
}

PUBLIC_METHOD float MeshDepth_internal(Entity* mesh)
{
	return bbMeshDepth((MeshModel*)mesh);
}

PUBLIC_METHOD int MeshesIntersect_internal(Entity* meshA, Entity* meshB)
{
	return bbMeshesIntersect((MeshModel*)meshA, (MeshModel*)meshB) != 0;
}

PUBLIC_METHOD int CountSurfaces_internal(Entity* mesh)
{
	return bbCountSurfaces((MeshModel*)mesh);
}

PUBLIC_METHOD Surface* GetSurface_internal(Entity* mesh, int surfaceIndex)
{
	return bbGetSurface((MeshModel*)mesh, surfaceIndex);
}

PUBLIC_METHOD void MeshCullBox_internal(Entity* mesh, float x, float y, float z, float width, float height, float depth)
{
	bbMeshCullBox((MeshModel*)mesh, x, y, z, width, height, depth);
}

PUBLIC_METHOD Surface* CreateSurface_internal(Entity* mesh, Brush* brush)
{
	return bbCreateSurface((MeshModel*)mesh, brush);
}

PUBLIC_METHOD Brush* GetSurfaceBrush_internal(Surface* surface)
{
	return bbGetSurfaceBrush(surface);
}

PUBLIC_METHOD Brush* GetEntityBrush_internal(Entity* entity)
{
	return bbGetEntityBrush((Model*)entity);
}

PUBLIC_METHOD Surface* FindSurface_internal(Entity* mesh, Brush* brush)
{
	return bbFindSurface((MeshModel*)mesh, brush);
}

PUBLIC_METHOD void ClearSurface_internal(Surface* surface, int clearVertices, int clearTriangles)
{
	bbClearSurface(surface, clearVertices ? 1 : 0, clearTriangles ? 1 : 0);
}

PUBLIC_METHOD void PaintSurface_internal(Surface* surface, Brush* brush)
{
	bbPaintSurface(surface, brush);
}

PUBLIC_METHOD int AddVertex_internal(Surface* surface, float x, float y, float z, float u, float v, float w)
{
	return bbAddVertex(surface, x, y, z, u, v, w);
}

PUBLIC_METHOD int AddTriangle_internal(Surface* surface, int v0, int v1, int v2)
{
	return bbAddTriangle(surface, v0, v1, v2);
}

PUBLIC_METHOD void VertexCoords_internal(Surface* surface, int index, float x, float y, float z)
{
	bbVertexCoords(surface, index, x, y, z);
}

PUBLIC_METHOD void VertexNormal_internal(Surface* surface, int index, float nx, float ny, float nz)
{
	bbVertexNormal(surface, index, nx, ny, nz);
}

PUBLIC_METHOD void VertexColor_internal(Surface* surface, int index, float red, float green, float blue, float alpha)
{
	bbVertexColor(surface, index, red, green, blue, alpha);
}

PUBLIC_METHOD void VertexTexCoords_internal(Surface* surface, int index, float u, float v, float w, int coordSet)
{
	bbVertexTexCoords(surface, index, u, v, w, coordSet);
}

PUBLIC_METHOD int CountVertices_internal(Surface* surface)
{
	return bbCountVertices(surface);
}

PUBLIC_METHOD int CountTriangles_internal(Surface* surface)
{
	return bbCountTriangles(surface);
}

PUBLIC_METHOD float VertexX_internal(Surface* surface, int index)
{
	return bbVertexX(surface, index);
}

PUBLIC_METHOD float VertexY_internal(Surface* surface, int index)
{
	return bbVertexY(surface, index);
}

PUBLIC_METHOD float VertexZ_internal(Surface* surface, int index)
{
	return bbVertexZ(surface, index);
}

PUBLIC_METHOD float VertexNX_internal(Surface* surface, int index)
{
	return bbVertexNX(surface, index);
}

PUBLIC_METHOD float VertexNY_internal(Surface* surface, int index)
{
	return bbVertexNY(surface, index);
}

PUBLIC_METHOD float VertexNZ_internal(Surface* surface, int index)
{
	return bbVertexNZ(surface, index);
}

PUBLIC_METHOD float VertexRed_internal(Surface* surface, int index)
{
	return bbVertexRed(surface, index);
}

PUBLIC_METHOD float VertexGreen_internal(Surface* surface, int index)
{
	return bbVertexGreen(surface, index);
}

PUBLIC_METHOD float VertexBlue_internal(Surface* surface, int index)
{
	return bbVertexBlue(surface, index);
}

PUBLIC_METHOD float VertexAlpha_internal(Surface* surface, int index)
{
	return bbVertexAlpha(surface, index);
}

PUBLIC_METHOD float VertexU_internal(Surface* surface, int index, int coordSet)
{
	return bbVertexU(surface, index, coordSet);
}

PUBLIC_METHOD float VertexV_internal(Surface* surface, int index, int coordSet)
{
	return bbVertexV(surface, index, coordSet);
}

PUBLIC_METHOD float VertexW_internal(Surface* surface, int index, int coordSet)
{
	return bbVertexW(surface, index, coordSet);
}

PUBLIC_METHOD int TriangleVertex_internal(Surface* surface, int index, int vertex)
{
	return bbTriangleVertex(surface, index, vertex);
}

PUBLIC_METHOD Entity* CreateCamera_internal(Entity* parent)
{
	return bbCreateCamera(parent);
}

PUBLIC_METHOD void CameraZoom_internal(Entity* camera, float zoom)
{
	bbCameraZoom((Camera*)camera, zoom);
}

PUBLIC_METHOD void CameraRange_internal(Entity* camera, float nr, float fr)
{
	bbCameraRange((Camera*)camera, nr, fr);
}

PUBLIC_METHOD void CameraClsColor_internal(Entity* camera, float red, float green, float blue)
{
	bbCameraClsColor((Camera*)camera, red, green, blue);
}

PUBLIC_METHOD void CameraClsMode_internal(Entity* camera, int color, int zBuffer)
{
	bbCameraClsMode((Camera*)camera, color ? 1 : 0, zBuffer ? 1 : 0);
}

PUBLIC_METHOD void CameraProjMode_internal(Entity* camera, int mode)
{
	bbCameraProjMode((Camera*)camera, mode);
}

PUBLIC_METHOD void CameraViewport_internal(Entity* camera, int x, int y, int width, int height)
{
	bbCameraViewport((Camera*)camera, x, y, width, height);
}

PUBLIC_METHOD void CameraFogColor_internal(Entity* camera, float red, float green, float blue)
{
	bbCameraFogColor((Camera*)camera, red, green, blue);
}

PUBLIC_METHOD void CameraFogRange_internal(Entity* camera, float nr, float fr)
{
	bbCameraFogRange((Camera*)camera, nr, fr);
}

PUBLIC_METHOD void CameraFogMode_internal(Entity* camera, int mode)
{
	bbCameraFogMode((Camera*)camera, mode);
}

PUBLIC_METHOD int CameraProject_internal(Entity* camera, float x, float y, float z)
{
	return bbCameraProject((Camera*)camera, x, y, z);
}

PUBLIC_METHOD float ProjectedX()
{
	return bbProjectedX();
}

PUBLIC_METHOD float ProjectedY()
{
	return bbProjectedY();
}

PUBLIC_METHOD float ProjectedZ()
{
	return bbProjectedZ();
}

PUBLIC_METHOD int EntityInView_internal(Entity* entity, Entity* camera)
{
	return bbEntityInView(entity, (Camera*)camera) != 0;
}

PUBLIC_METHOD int EntityVisible_internal(Entity* src, Entity* dest)
{
	return bbEntityVisible((Object*)src, (Object*)dest) != 0;
}

PUBLIC_METHOD Entity* EntityPick_internal(Entity* src, float range)
{
	return bbEntityPick((Object*)src, range);
}

PUBLIC_METHOD Entity* LinePick_internal(float x, float y, float z, float dx, float dy, float dz, float radius)
{
	return bbLinePick(x, y, z, dx, dy, dz, radius);
}

PUBLIC_METHOD Entity* CameraPick_internal(Entity* camera, float viewportX, float viewportY)
{
	return bbCameraPick((Camera*)camera, viewportX, viewportY);
}

PUBLIC_METHOD float PickedX()
{
	return bbPickedX();
}

PUBLIC_METHOD float PickedY()
{
	return bbPickedY();
}

PUBLIC_METHOD float PickedZ()
{
	return bbPickedZ();
}

PUBLIC_METHOD float PickedNX()
{
	return bbPickedNX();
}

PUBLIC_METHOD float PickedNY()
{
	return bbPickedNY();
}

PUBLIC_METHOD float PickedNZ()
{
	return bbPickedNZ();
}

PUBLIC_METHOD float PickedTime()
{
	return bbPickedTime();
}

PUBLIC_METHOD Entity* PickedEntity_internal()
{
	return bbPickedEntity();
}

PUBLIC_METHOD Surface* PickedSurface_internal()
{
	return (Surface*)bbPickedSurface();
}

PUBLIC_METHOD int PickedTriangle()
{
	return bbPickedTriangle();
}

PUBLIC_METHOD Entity* CreateLight_internal(int type, Entity* parent)
{
	return bbCreateLight(type, parent);
}

PUBLIC_METHOD void LightColor_internal(Entity* light, float red, float green, float blue)
{
	bbLightColor((Light*)light, red, green, blue);
}

PUBLIC_METHOD void LightRange_internal(Entity* light, float range)
{
	bbLightRange((Light*)light, range);
}

PUBLIC_METHOD void LightConeAngles_internal(Entity* light, float innerAngle, float outerAngle)
{
	bbLightConeAngles((Light*)light, innerAngle, outerAngle);
}

PUBLIC_METHOD Entity* CreatePivot_internal(Entity* parent)
{
	return bbCreatePivot(parent);
}

PUBLIC_METHOD Entity* CreateSprite_internal(Entity* parent)
{
	return bbCreateSprite(parent);
}

PUBLIC_METHOD Entity* LoadSprite_internal(const char* file, int textureFlags, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadSprite(f, textureFlags, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void RotateSprite_internal(Entity* sprite, float angle)
{
	bbRotateSprite((Sprite*)sprite, angle);
}

PUBLIC_METHOD void ScaleSprite_internal(Entity* sprite, float xScale, float yScale)
{
	bbScaleSprite((Sprite*)sprite, xScale, yScale);
}

PUBLIC_METHOD void HandleSprite_internal(Entity* sprite, float xHandle, float yHandle)
{
	bbHandleSprite((Sprite*)sprite, xHandle, yHandle);
}

PUBLIC_METHOD void SpriteViewMode_internal(Entity* sprite, int viewMode)
{
	bbSpriteViewMode((Sprite*)sprite, viewMode);
}

PUBLIC_METHOD Entity* LoadMD2_internal(const char* file, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadMD2(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void AnimateMD2_internal(Entity* md2, int mode, float speed, int firstFrame, int lastFrame, float transition)
{
	bbAnimateMD2((MD2Model*)md2, mode, speed, firstFrame, lastFrame, transition);
}

PUBLIC_METHOD float MD2AnimTime_internal(Entity* md2)
{
	return bbMD2AnimTime((MD2Model*)md2);
}

PUBLIC_METHOD int MD2AnimLength_internal(Entity* md2)
{
	return bbMD2AnimLength((MD2Model*)md2);
}

PUBLIC_METHOD int MD2Animating_internal(Entity* md2)
{
	return bbMD2Animating((MD2Model*)md2) != 0;
}

PUBLIC_METHOD Entity* LoadBSP_internal(const char* file, float gammaAdjust, Entity* parent)
{
	BBStr* f = toBBStr(file);
	Entity* ret = bbLoadBSP(f, gammaAdjust, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void BSPLighting_internal(Entity* bsp, int useLightmaps)
{
	bbBSPLighting((Q3BSPModel*)bsp, useLightmaps ? 1 : 0);
}

PUBLIC_METHOD void BSPAmbientLight_internal(Entity* bsp, float red, float green, float blue)
{
	bbBSPAmbientLight((Q3BSPModel*)bsp, red, green, blue);
}

PUBLIC_METHOD Entity* CreateMirror_internal(Entity* parent)
{
	return bbCreateMirror(parent);
}

PUBLIC_METHOD Entity* CreatePlane_internal(int segments, Entity* parent)
{
	return bbCreatePlane(segments, parent);
}

PUBLIC_METHOD Entity* CreateTerrain_internal(int gridSize, Entity* parent)
{
	return bbCreateTerrain(gridSize, parent);
}

PUBLIC_METHOD Entity* LoadTerrain_internal(const char* heightmapFile, Entity* parent)
{
	BBStr* f = toBBStr(heightmapFile);
	Entity* ret = bbLoadTerrain(f, parent);
	freeBBStr(f);
	return ret;
}

PUBLIC_METHOD void TerrainDetail_internal(Entity* terrain, int detailLevel, int morph)
{
	bbTerrainDetail((Terrain*)terrain, detailLevel, morph ? 1 : 0);
}

PUBLIC_METHOD void TerrainShading_internal(Entity* terrain, int enable)
{
	bbTerrainShading((Terrain*)terrain, enable ? 1 : 0);
}

PUBLIC_METHOD float TerrainX_internal(Entity* terrain, float worldX, float worldY, float worldZ)
{
	return bbTerrainX((Terrain*)terrain, worldX, worldY, worldZ);
}

PUBLIC_METHOD float TerrainY_internal(Entity* terrain, float worldX, float worldY, float worldZ)
{
	return bbTerrainY((Terrain*)terrain, worldX, worldY, worldZ);
}

PUBLIC_METHOD float TerrainZ_internal(Entity* terrain, float worldX, float worldY, float worldZ)
{
	return bbTerrainZ((Terrain*)terrain, worldX, worldY, worldZ);
}

PUBLIC_METHOD int TerrainSize_internal(Entity* terrain)
{
	return bbTerrainSize((Terrain*)terrain);
}

PUBLIC_METHOD float TerrainHeight_internal(Entity* terrain, int terrainX, int terrainZ)
{
	return bbTerrainHeight((Terrain*)terrain, terrainX, terrainZ);
}

PUBLIC_METHOD void ModifyTerrain_internal(Entity* terrain, int terrainX, int terrainZ, float height, int realtime)
{
	bbModifyTerrain((Terrain*)terrain, terrainX, terrainZ, height, realtime ? 1 : 0);
}

PUBLIC_METHOD Entity* CreateListener_internal(Entity* parent, float rolloffFactor, float dopplerScale, float distanceScale)
{
	return bbCreateListener(parent, rolloffFactor, dopplerScale, distanceScale);
}

PUBLIC_METHOD gxChannel* EmitSound_internal(gxSound* sound, Entity* entity)
{
	return bbEmitSound(sound, (Object*)entity);
}

PUBLIC_METHOD Entity* CopyEntity_internal(Entity* entity, Entity* parent)
{
	return bbCopyEntity(entity, parent);
}

PUBLIC_METHOD float EntityX_internal(Entity* entity, int global)
{
	return bbEntityX(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityY_internal(Entity* entity, int global)
{
	return bbEntityY(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityZ_internal(Entity* entity, int global)
{
	return bbEntityZ(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityPitch_internal(Entity* entity, int global)
{
	return bbEntityPitch(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityYaw_internal(Entity* entity, int global)
{
	return bbEntityYaw(entity, global ? 1 : 0);
}

PUBLIC_METHOD float EntityRoll_internal(Entity* entity, int global)
{
	return bbEntityRoll(entity, global ? 1 : 0);
}

PUBLIC_METHOD float GetMatElement_internal(Entity* entity, int row, int column)
{
	return bbGetMatElement(entity, row, column);
}

PUBLIC_METHOD void TFormPoint_internal(float x, float y, float z, Entity* src, Entity* dest)
{
	bbTFormPoint(x, y, z, src, dest);
}

PUBLIC_METHOD void TFormVector_internal(float x, float y, float z, Entity* src, Entity* dest)
{
	bbTFormVector(x, y, z, src, dest);
}

PUBLIC_METHOD void TFormNormal_internal(float x, float y, float z, Entity* src, Entity* dest)
{
	bbTFormNormal(x, y, z, src, dest);
}

PUBLIC_METHOD float TFormedX()
{
	return bbTFormedX();
}

PUBLIC_METHOD float TFormedY()
{
	return bbTFormedY();
}

PUBLIC_METHOD float TFormedZ()
{
	return bbTFormedZ();
}

PUBLIC_METHOD float VectorYaw(float x, float y, float z)
{
	return bbVectorYaw(x, y, z);
}

PUBLIC_METHOD float VectorPitch(float x, float y, float z)
{
	return bbVectorPitch(x, y, z);
}

PUBLIC_METHOD float DeltaPitch_internal(Entity* src, Entity* dest)
{
	return bbDeltaPitch(src, dest);
}

PUBLIC_METHOD float DeltaYaw_internal(Entity* src, Entity* dest)
{
	return bbDeltaYaw(src, dest);
}

PUBLIC_METHOD void ResetEntity_internal(Entity* entity)
{
	bbResetEntity((Object*)entity);
}

PUBLIC_METHOD void EntityType_internal(Entity* entity, int collisionType, int recursive)
{
	bbEntityType((Object*)entity, collisionType, recursive ? 1 : 0);
}

PUBLIC_METHOD void EntityPickMode_internal(Entity* entity, int mode, int obscurer)
{
	bbEntityPickMode((Object*)entity, mode, obscurer ? 1 : 0);
}

PUBLIC_METHOD Entity* GetParent_internal(Entity* entity)
{
	return bbGetParent(entity);
}

PUBLIC_METHOD int GetEntityType_internal(Entity* entity)
{
	return bbGetEntityType((Object*)entity);
}

PUBLIC_METHOD void EntityRadius_internal(Entity* entity, float xRadius, float yRadius)
{
	bbEntityRadius((Object*)entity, xRadius, yRadius);
}

PUBLIC_METHOD void EntityBox_internal(Entity* entity, float x, float y, float z, float width, float height, float depth)
{
	bbEntityBox((Object*)entity, x, y, z, width, height, depth);
}

PUBLIC_METHOD float EntityDistance_internal(Entity* src, Entity* dest)
{
	return bbEntityDistance(src, dest);
}

PUBLIC_METHOD Entity* EntityCollided_internal(Entity* entity, int type)
{
	return (Entity*)bbEntityCollided((Object*)entity, type);
}

PUBLIC_METHOD int CountCollisions_internal(Entity* entity)
{
	return bbCountCollisions((Object*)entity);
}

PUBLIC_METHOD float CollisionX_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionX((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionY_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionY((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionZ_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionZ((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionNX_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionNX((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionNY_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionNY((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionNZ_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionNZ((Object*)entity, collisionIndex);
}

PUBLIC_METHOD float CollisionTime_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionTime((Object*)entity, collisionIndex);
}

PUBLIC_METHOD Entity* CollisionEntity_internal(Entity* entity, int collisionIndex)
{
	return (Entity*)bbCollisionEntity((Object*)entity, collisionIndex);
}

PUBLIC_METHOD Surface* CollisionSurface_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionSurface((Object*)entity, collisionIndex);
}

PUBLIC_METHOD int CollisionTriangle_internal(Entity* entity, int collisionIndex)
{
	return bbCollisionTriangle((Object*)entity, collisionIndex);
}

PUBLIC_METHOD void MoveEntity_internal(Entity* entity, float x, float y, float z)
{
	bbMoveEntity(entity, x, y, z);
}

PUBLIC_METHOD void TurnEntity_internal(Entity* entity, float pitch, float yaw, float roll, int global)
{
	bbTurnEntity(entity, pitch, yaw, roll, global ? 1 : 0);
}

PUBLIC_METHOD void TranslateEntity_internal(Entity* entity, float x, float y, float z, int global)
{
	bbTranslateEntity(entity, x, y, z, global ? 1 : 0);
}

PUBLIC_METHOD void PositionEntity_internal(Entity* entity, float x, float y, float z, int global)
{
	bbPositionEntity(entity, x, y, z, global ? 1 : 0);
}

PUBLIC_METHOD void ScaleEntity_internal(Entity* entity, float xScale, float yScale, float zScale, int global)
{
	bbScaleEntity(entity, xScale, yScale, zScale, global ? 1 : 0);
}

PUBLIC_METHOD void RotateEntity_internal(Entity* entity, float pitch, float yaw, float roll, int global)
{
	bbRotateEntity(entity, pitch, yaw, roll, global ? 1 : 0);
}

PUBLIC_METHOD void PointEntity_internal(Entity* entity, Entity* target, float roll)
{
	bbPointEntity(entity, target, roll);
}

PUBLIC_METHOD void AlignToVector_internal(Entity* entity, float vectorX, float vectorY, float vectorZ, int axis, float rate)
{
	bbAlignToVector(entity, vectorX, vectorY, vectorZ, axis, rate);
}

PUBLIC_METHOD void SetAnimTime_internal(Entity* entity, float time, int animSeq)
{
	bbSetAnimTime((Object*)entity, time, animSeq);
}

PUBLIC_METHOD void Animate_internal(Entity* entity, int mode, float speed, int sequence, float transition)
{
	bbAnimate((Object*)entity, mode, speed, sequence, transition);
}

PUBLIC_METHOD void SetAnimKey_internal(Entity* entity, int frame, int posKey, int rotKey, int scaleKey)
{
	bbSetAnimKey((Object*)entity, frame, posKey ? 1 : 0, rotKey ? 1 : 0, scaleKey ? 1 : 0);
}

PUBLIC_METHOD int AddAnimSeq_internal(Entity* entity, int length)
{
	return bbAddAnimSeq((Object*)entity, length);
}

PUBLIC_METHOD int ExtractAnimSeq_internal(Entity* entity, int firstFrame, int lastFrame, int animSeq)
{
	return bbExtractAnimSeq((Object*)entity, firstFrame, lastFrame, animSeq);
}

PUBLIC_METHOD int AnimSeq_internal(Entity* entity)
{
	return bbAnimSeq((Object*)entity);
}

PUBLIC_METHOD float AnimTime_internal(Entity* entity)
{
	return bbAnimTime((Object*)entity);
}

PUBLIC_METHOD int AnimLength_internal(Entity* entity)
{
	return bbAnimLength((Object*)entity);
}

PUBLIC_METHOD int Animating_internal(Entity* entity)
{
	return bbAnimating((Object*)entity) != 0;
}

PUBLIC_METHOD void EntityParent_internal(Entity* entity, Entity* parent, int global)
{
	bbEntityParent(entity, parent, global ? 1 : 0);
}

PUBLIC_METHOD int CountChildren_internal(Entity* entity)
{
	return bbCountChildren(entity);
}

PUBLIC_METHOD Entity* GetChild_internal(Entity* entity, int index)
{
	return bbGetChild(entity, index);
}

PUBLIC_METHOD Entity* FindChild_internal(Entity* entity, const char* name)
{
	BBStr* n = toBBStr(name);
	Entity* ret = bbFindChild(entity, n);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void PaintEntity_internal(Entity* entity, Brush* brush)
{
	bbPaintEntity((Model*)entity, brush);
}

PUBLIC_METHOD void EntityColor_internal(Entity* entity, float red, float green, float blue)
{
	bbEntityColor((Model*)entity, red, green, blue);
}

PUBLIC_METHOD void EntityAlpha_internal(Entity* entity, float alpha)
{
	bbEntityAlpha((Model*)entity, alpha);
}

PUBLIC_METHOD void EntityShininess_internal(Entity* entity, float shininess)
{
	bbEntityShininess((Model*)entity, shininess);
}

PUBLIC_METHOD void EntityTexture_internal(Entity* entity, Texture* texture, int frame, int index)
{
	bbEntityTexture((Model*)entity, texture, frame, index);
}

PUBLIC_METHOD void EntityBlend_internal(Entity* entity, int blend)
{
	bbEntityBlend((Model*)entity, blend);
}

PUBLIC_METHOD void EntityFX_internal(Entity* entity, int fx)
{
	bbEntityFX((Model*)entity, fx);
}

PUBLIC_METHOD void EntityAutoFade_internal(Entity* entity, float nr, float fr)
{
	bbEntityAutoFade((Model*)entity, nr, fr);
}

PUBLIC_METHOD void EntityOrder_internal(Entity* entity, int order)
{
	bbEntityOrder((Object*)entity, order);
}

PUBLIC_METHOD void HideEntity_internal(Entity* entity)
{
	bbHideEntity(entity);
}

PUBLIC_METHOD void ShowEntity_internal(Entity* entity)
{
	bbShowEntity(entity);
}

PUBLIC_METHOD int EntityHidden_internal(Entity* entity)
{
  return bbEntityHidden(entity) != 0;
}

PUBLIC_METHOD void FreeEntity_internal(Entity* entity)
{
	bbFreeEntity(entity);
}

PUBLIC_METHOD void NameEntity_internal(Entity* entity, const char* name)
{
	BBStr* n = toBBStr(name);
	bbNameEntity(entity, n);
	freeBBStr(n);
}

PUBLIC_METHOD void EntityName_internal(char* ret, int retLen, Entity* entity)
{
    strcpy_s(ret, retLen, toMonoStr(bbEntityName(entity)));
}

PUBLIC_METHOD void EntityClass_internal(char* ret, int retLen, Entity* entity)
{
    strcpy_s(ret, retLen, toMonoStr(bbEntityClass(entity)));
}

PUBLIC_METHOD void GetBuildType_internal(char* ret, int retLen)
{
    strcpy_s(ret, retLen, toMonoStr(bbGetBuildType()));
}