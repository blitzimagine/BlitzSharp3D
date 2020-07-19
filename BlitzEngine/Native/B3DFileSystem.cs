using System;
using System.IO;

namespace BlitzEngine
{
	public static partial class Blitz3D
	{
		// ----------
		// FileSystem
		// ----------

		public const int FILE_TYPE_NONE = 0;
		public const int FILE_TYPE_FILE = 1;
		public const int FILE_TYPE_DIR = 2;

		public static File OpenFile(string filename)
		{
			if(!System.IO.File.Exists(filename))
			{
				return null;
			}
			return new File(filename,FileMode.Open, FileAccess.ReadWrite);
		}
		public static File ReadFile(string filename)
		{
			if(!System.IO.File.Exists(filename))
			{
				return null;
			}
			return new File(filename,FileMode.Open, FileAccess.Read);
		}
		public static File WriteFile(string filename)
		{
			return new File(filename,FileMode.Create, FileAccess.Write);
		}
		public static void CloseFile(File file)
		{
			file.stream.Close();
		}
		public static int FilePos(File file)
		{
			return (int)file.stream.Position;
		}
		public static int SeekFile(File file, int pos)
		{
			return (int)file.stream.Seek(pos, SeekOrigin.Begin);
		}

		public static Dir ReadDir(string dir) => new Dir(dir);
		
		public static void CloseDir(Dir dir) => dir.Close();
		
		public static string NextFile(Dir dir) => dir.GetNextFile();
		
		public static string CurrentDir() => Environment.CurrentDirectory;
		
		public static void ChangeDir(string dir) => Environment.CurrentDirectory = dir;

		public static void CreateDir(string dir) => Directory.CreateDirectory(dir);

		public static void DeleteDir(string dir) => Directory.Delete(dir);

		public static int FileSize(string file) => (int)new FileInfo(file).Length;

		public static int FileType(string file)
		{
			if(System.IO.File.Exists(file))
			{
				return FILE_TYPE_FILE;
			}
			if(Directory.Exists(file))
			{
				return FILE_TYPE_DIR;
			}
			return FILE_TYPE_NONE;
		}

		public static void CopyFile(string file, string to) => System.IO.File.Copy(file, to, true);

		public static void DeleteFile(string file) => System.IO.File.Delete(file);
	}
}
