using System.IO;

namespace BlitzEngine
{
	public class File : Stream
	{
		internal System.IO.Stream stream;

		public File(string fileName, FileMode mode, FileAccess access)
		{
			stream = new FileStream(fileName,mode,access);
		}

		~File()
		{
			stream = null;
		}

		//returns chars read
		public override int Read(byte[] buff, int offset, int size) => stream.Read(buff, offset, size);

		//returns chars written
		public override int Write(byte[] buff, int offset, int size)
		{
			stream.Write(buff, offset, size);
			return size;
		}


		//returns chars avilable for reading
		public override int Avail() => (int)(stream.Length-stream.Position);

		//returns EOF status
		public override bool Eof() => stream.Position >= stream.Length;
	}
}
