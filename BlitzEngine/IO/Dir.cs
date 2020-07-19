using System.Collections.Generic;
using System.IO;

namespace BlitzEngine
{
	public class Dir
	{
		private readonly string path;
		private readonly IEnumerator<string> files;
		private readonly IEnumerator<string> folders;

		public Dir(string path) 
		{
			this.path = path;
			string[] fileArray = Directory.GetFiles(path,"*",SearchOption.TopDirectoryOnly);
			string[] folderArray = Directory.GetDirectories(path,"*",SearchOption.TopDirectoryOnly);
			files = ((IList<string>)fileArray).GetEnumerator();
			folders = ((IList<string>)folderArray).GetEnumerator();
		}

		public string GetNextFile()
		{
			if(files.MoveNext())
			{
				return Path.GetFileName(files.Current);
			}
			if(folders.MoveNext())
			{
				return new DirectoryInfo(folders.Current).Name;
			}
			return "";
		}

		public static Dir Read(string d) => new Dir(d);//gx_filesys.openDir(d, 0);

		public void Close(){}//gx_filesys.closeDir(this);
	}
}
