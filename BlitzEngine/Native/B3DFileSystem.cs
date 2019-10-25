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
		// ----------
		// FileSystem
		// ----------

		[DllImport(B3DDllLink)]
		private static extern IntPtr OpenFile_internal(string filename);

		public static File OpenFile(string filename)
		{
			IntPtr pointer = OpenFile_internal(filename);
			File file = new File(pointer);
			return file;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr ReadFile_internal(string filename);

		public static File ReadFile(string filename)
		{
			IntPtr pointer = ReadFile_internal(filename);
			File file = new File(pointer);
			return file;
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr WriteFile_internal(string filename);

		public static File WriteFile(string filename)
		{
			IntPtr pointer = WriteFile_internal(filename);
			File file = new File(pointer);
			return file;
		}

		[DllImport(B3DDllLink)]
		private static extern void CloseFile_internal(IntPtr file);

		public static void CloseFile(File file)
		{
			CloseFile_internal(file.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int FilePos_internal(IntPtr file);

		public static int FilePos(File file)
		{
			return FilePos_internal(file.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern int SeekFile_internal(IntPtr file, int pos);

		public static int SeekFile(File file, int pos)
		{
			return SeekFile_internal(file.Pointer, pos);
		}

		[DllImport(B3DDllLink)]
		private static extern IntPtr ReadDir_internal(string dir);

		public static Dir ReadDir(string dir)
		{
			IntPtr pointer = ReadDir_internal(dir);
			Dir ret = new Dir(pointer);
			return ret;
		}

		[DllImport(B3DDllLink)]
		private static extern void CloseDir_internal(IntPtr dir);

		public static void CloseDir(Dir dir)
		{
			CloseDir_internal(dir.Pointer);
		}

		[DllImport(B3DDllLink)]
		private static extern void NextFile_internal(StringBuilder ret, int retLen, IntPtr dir);

		public static string NextFile(Dir dir)
		{
			StringBuilder sb = new StringBuilder(4096);
			NextFile_internal(sb, sb.Capacity, dir.Pointer);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern void CurrentDir_internal(StringBuilder ret, int retLen);

		public static string CurrentDir()
		{
			StringBuilder sb = new StringBuilder(4096);
			CurrentDir_internal(sb, sb.Capacity);
			return sb.ToString();
		}

		[DllImport(B3DDllLink)]
		public static extern void ChangeDir(string dir);

		[DllImport(B3DDllLink)]
		public static extern void CreateDir(string dir);

		[DllImport(B3DDllLink)]
		public static extern void DeleteDir(string dir);

		[DllImport(B3DDllLink)]
		public static extern int FileSize(string file);

		[DllImport(B3DDllLink)]
		public static extern int FileType(string file);

		[DllImport(B3DDllLink)]
		private static extern void CopyFile_internal(string file, string to);

		public static void CopyFile(string file, string to) => CopyFile_internal(file, to);

		[DllImport(B3DDllLink)]
		private static extern void DeleteFile_internal(string file);

		public static void DeleteFile(string file) => DeleteFile_internal(file);
	}
}
