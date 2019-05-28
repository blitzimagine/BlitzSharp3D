using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// -----
		// Audio
		// -----

		[DllImport(B3DDllLink)]
		private static extern IntPtr LoadSound_internal(string filename);

		public static Sound LoadSound(string filename)
		{
			IntPtr pointer = LoadSound_internal(filename);
			Sound ret = new Sound(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void FreeSound_internal(IntPtr sound);

		public static void FreeSound(Sound sound)
		{
			FreeSound_internal(sound.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void LoopSound_internal(IntPtr sound);

		public static void LoopSound(Sound sound)
		{
			LoopSound_internal(sound.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void SoundPitch_internal(IntPtr sound, int pitch);

		public static void SoundPitch(Sound sound, int pitch)
		{
			SoundPitch_internal(sound.Pointer, pitch);
		}

		[DllImport(B3DDllLink)]
		private static extern void SoundVolume_internal(IntPtr sound, float volume);

		public static void SoundVolume(Sound sound, float volume)
		{
			SoundVolume_internal(sound.Pointer, volume);
		}

		[DllImport(B3DDllLink)]
		private static extern void SoundPan_internal(IntPtr sound, float pan);

		public static void SoundPan(Sound sound, float pan)
		{
			SoundPan_internal(sound.Pointer, pan);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr PlaySound_internal(IntPtr sound);

		public static Channel PlaySound(Sound sound)
		{
			IntPtr pointer = PlaySound_internal(sound.Pointer);
			Channel ret = new Channel(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr PlayMusic_internal(string filename);

		public static Channel PlayMusic(string filename)
		{
			IntPtr pointer = PlayMusic_internal(filename);
			Channel ret = new Channel(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr PlayCDTrack_internal(int track, int mode);

		public static Channel PlayCDTrack(int track, int mode = 1)
		{
			IntPtr pointer = PlayCDTrack_internal(track, mode);
			Channel ret = new Channel(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void StopChannel_internal(IntPtr channel);

		public static void StopChannel(Channel channel)
		{
			if (channel != null && channel.Pointer != IntPtr.Zero)
			{
				StopChannel_internal(channel.Pointer);
				channel.Pointer = IntPtr.Zero;
			}
		}

		[DllImport(B3DDllLink)]
		private static extern void PauseChannel_internal(IntPtr channel);

		public static void PauseChannel(Channel channel)
		{
			PauseChannel_internal(channel.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void ResumeChannel_internal(IntPtr channel);

		public static void ResumeChannel(Channel channel)
		{
			ResumeChannel_internal(channel.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void ChannelPitch_internal(IntPtr channel, int pitch);

		public static void ChannelPitch(Channel channel, int pitch)
		{
			ChannelPitch_internal(channel.Pointer, pitch);
		}

		[DllImport(B3DDllLink)]
		private static extern void ChannelVolume_internal(IntPtr channel, float volume);

		public static void ChannelVolume(Channel channel, float volume)
		{
			ChannelVolume_internal(channel.Pointer, volume);
		}

		[DllImport(B3DDllLink)]
		private static extern void ChannelPan_internal(IntPtr channel, float pan);

		public static void ChannelPan(Channel channel, float pan)
		{
			ChannelPan_internal(channel.Pointer, pan);
		}

		[DllImport(B3DDllLink)]
		private static extern bool ChannelPlaying_internal(IntPtr channel);

		public static bool ChannelPlaying(Channel channel)
		{
			return ChannelPlaying_internal(channel.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr Load3DSound_internal(string filename);

		public static Sound Load3DSound(string filename)
		{
			IntPtr pointer = Load3DSound_internal(filename);
			Sound ret = new Sound(pointer);
			return ret;
		}
	}
}
