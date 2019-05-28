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
		// ------
		// Stream
		// ------

		[DllImport(B3DDllLink)]
		private static extern bool Eof_internal(IntPtr stream);

		public static bool Eof(Stream stream)
		{
			return Eof_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int ReadAvail_internal(IntPtr stream);

		public static int ReadAvail(Stream stream)
		{
			return ReadAvail_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern byte ReadByte_internal(IntPtr stream);

		public static byte ReadByte(Stream stream)
		{
			return ReadByte_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern short ReadShort_internal(IntPtr stream);

		public static short ReadShort(Stream stream)
		{
			return ReadShort_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int ReadInt_internal(IntPtr stream);

		public static int ReadInt(Stream stream)
		{
			return ReadInt_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern float ReadFloat_internal(IntPtr stream);

		public static float ReadFloat(Stream stream)
		{
			return ReadFloat_internal(stream.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void ReadString_internal(StringBuilder ret, int retLen, IntPtr stream);

		public static string ReadString(Stream stream)
		{
			StringBuilder sb = new StringBuilder(4096);
			ReadString_internal(sb, sb.Capacity, stream.Pointer);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		private static extern void ReadLine_internal(StringBuilder ret, int retLen, IntPtr stream);

		public static string ReadLine(Stream stream)
		{
			StringBuilder sb = new StringBuilder(4096);
			ReadLine_internal(sb, sb.Capacity, stream.Pointer);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		private static extern void WriteByte_internal(IntPtr stream, byte b);

		public static void WriteByte(Stream stream, byte b)
		{
			WriteByte_internal(stream.Pointer, b);
		}

		[DllImport(B3DDllLink)]
		private static extern void WriteShort_internal(IntPtr stream, short s);

		public static void WriteShort(Stream stream, short s)
		{
			WriteShort_internal(stream.Pointer, s);
		}

		[DllImport(B3DDllLink)]
		private static extern void WriteInt_internal(IntPtr stream, int i);

		public static void WriteInt(Stream stream, int i)
		{
			WriteInt_internal(stream.Pointer, i);
		}

		[DllImport(B3DDllLink)]
		private static extern void WriteFloat_internal(IntPtr stream, float f);

		public static void WriteFloat(Stream stream, float f)
		{
			WriteFloat_internal(stream.Pointer, f);
		}

		[DllImport(B3DDllLink)]
		private static extern void WriteString_internal(IntPtr stream, string s);

		public static void WriteString(Stream stream, string s)
		{
			WriteString_internal(stream.Pointer, s);
		}

		[DllImport(B3DDllLink)]
		private static extern void WriteLine_internal(IntPtr stream, string s);

		public static void WriteLine(Stream stream, string s)
		{
			WriteLine_internal(stream.Pointer, s);
		}

		[DllImport(B3DDllLink)]
		private static extern void CopyStream_internal(IntPtr src, IntPtr dest, int bufferSize);

		public static void CopyStream(Stream src, Stream dest, int bufferSize = 16384)
		{
			CopyStream_internal(src.Pointer, dest.Pointer, bufferSize);
		}
	}
}
