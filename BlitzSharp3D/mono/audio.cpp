#include "monoutil.h"
#include "../bbruntime/bbaudio.h"

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